// Driver program that measures the performance of synchronization
// @(#)synch_driver.cpp	1.1	10/18/96

// mechanisms provided by ACE and the underlying OS.

#include "ace/Service_Config.h"
#include "ace/Service_Repository.h"
#include "ace/Synch.h"
#include "Options.h"
#include "Benchmark.h"

#if defined (ACE_HAS_THREADS)

class Benchmark_Test : public ACE_Service_Config
{
public:
  Benchmark_Test (void);
  int init (int argc, char **argv);

private:
  void run_test (void);

  virtual int handle_signal (int signum
#if defined (ACE_HAS_SIGINFO_T)
, siginfo_t * = 0, ucontext_t * = 0
#endif /* ACE_HAS_SIGINFO_T */
);
  
  int n_lwps_;
  int orig_n_lwps_;
};

int
Benchmark_Test::handle_signal (int signum
#if defined (ACE_HAS_SIGINFO_T)
, siginfo_t *, ucontext_t *
#endif /* ACE_HAS_SIGINFO_T */
)
{
  ACE_DEBUG ((LM_DEBUG, "caught %S, shutting down the test%a\n", signum, 1));
  return 0;
}

Benchmark_Test::Benchmark_Test (void)
  : ACE_Service_Config (1), // Do not load default services
    n_lwps_ (0), 
    orig_n_lwps_ (0) 
{
  ACE_Service_Config::reactor ()->register_handler (SIGINT, this);
}

void
Benchmark_Test::run_test (void)
{
  // Tell the threads that we are not finished.
  Benchmark::done (0);
  
  // Allow thread(s) to make progress.
  ACE_Service_Config::thr_mgr ()->resume_all ();

  ACE_Time_Value timeout (options.sleep_time ());

  ACE_DEBUG ((LM_DEBUG, "starting timer\n"));
  options.start_timer ();

  ACE_OS::select (0, 0, 0, 0, &timeout);
  options.stop_timer ();
  ACE_DEBUG ((LM_DEBUG, "stopping timer\n"));

  // Stop thread(s) from making any further progress.
  ACE_Service_Config::thr_mgr ()->suspend_all (); 

  // Tell the threads that we are finished.
  Benchmark::done (1);
  
  ACE_DEBUG ((LM_DEBUG, "------------------------------------------------------------------------\n"));
  ACE_DEBUG ((LM_DEBUG, "targ 0x%x (%s, %s, %s)\n"
	     "n_lwps_orig = %d, n_lwps_set = %d, n_lwps_end = %d\n",
	     options.t_flags (),
	     (options.t_flags () & THR_DETACHED) ? "THR_DETACHED" : "Not Detached",
	     (options.t_flags () & THR_BOUND)	? "THR_BOUND"    : "Not Bound",
	     (options.t_flags () & THR_NEW_LWP)  ? "THR_NEW_LWP"  : "No New_LWP",
	     this->orig_n_lwps_, this->n_lwps_, ACE_Thread::getconcurrency ()));

  int   count = options.count ();
  float rate  = count / (float (options.sleep_time ()));

  ACE_DEBUG ((LM_DEBUG, "to count = %d\nrate = %.3f ops/sec, per operation = %.2f usec\n",
	    count, rate, (1.0e6 / rate) / synch_count));
  options.print_results ();

  // Allow thread(s) to finish up.
  ACE_Service_Config::thr_mgr ()->resume_all ();

  // Wait for all the threads to exit. 
  ACE_Service_Config::thr_mgr ()->wait ();
  options.init ();
}

// Initialize and run the benchmarks tests.

Benchmark_Test::init (int argc, char **argv)
{
  options.parse_args (argc, argv);

  // Open the service configurator and process the directives in the
  // svc.conf file.

  if (this->open (argv[0]) == -1)
    ACE_ERROR_RETURN ((LM_ERROR, "ACE_Service_Config::open failed\n%a", 1), -1);

  ACE_Service_Repository_Iterator sri (*this->ACE_Service_Config::svc_rep ());
  
  // Iteratively execute each service loaded in from the svc.conf
  // file.

  for (const ACE_Service_Record *sr; 
       sri.next (sr) != 0; 
       sri.advance ())
    {
      // This would greatly benefit from RTTI typesafe downcasting...
      const ACE_Service_Type *type = sr->type ();
      const void *obj = type->object ();
      ACE_Service_Object *so = (ACE_Service_Object *) obj;
      Benchmark *bp = (Benchmark *) so;

      ACE_DEBUG ((LM_DEBUG, "\nstarting up %s\n", sr->name ()));

      this->orig_n_lwps_ = ACE_Thread::getconcurrency ();
      this->n_lwps_ = options.n_lwps ();

      if (this->n_lwps_ > 0)
	ACE_Thread::setconcurrency (this->n_lwps_);

      // We should probably use a "barrier" here rather than
      // THR_SUSPENDED since many OS platforms lack the ability to
      // create suspended threads...
      if (ACE_Service_Config::thr_mgr ()->spawn_n 
	  (options.thr_count (), ACE_THR_FUNC (bp->svc_run), 
	   (void *) bp, options.t_flags () | THR_SUSPENDED) == -1)
	ACE_ERROR ((LM_ERROR, "%p\n%a", "couldn't spawn threads", 1));

      this->run_test ();
    }

  return 0;
}

int
main (int argc, char *argv[])
{
  Benchmark_Test benchmark_tester;
  
  if (benchmark_tester.init (argc, argv) == -1)
    ACE_ERROR ((LM_ERROR, "%p\n%a", "open", 1));

  return 0;
}
#else
int
main (int, char *[])
{
  ACE_ERROR_RETURN ((LM_ERROR, 
		     "This test requires the platform to have threads\n"), -1);
}
#endif /* ACE_HAS_THREADS */
