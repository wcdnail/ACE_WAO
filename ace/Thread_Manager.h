/* -*- C++ -*- */
// $Id$


// ============================================================================
//
// = LIBRARY
//    ace
// 
// = FILENAME
//    Thread_Manager.h 
//
// = AUTHOR
//    Doug Schmidt 
// 
// ============================================================================

#if !defined (ACE_THREAD_MANAGER_H)
#define ACE_THREAD_MANAGER_H

#include "ace/Log_Msg.h"
#include "ace/Thread.h"
#include "ace/Synch.h"

class ACE_Thread_Manager;

class ACE_Export ACE_Thread_Descriptor
  // = Title
  //    Information for controlling threads that run under the control
  //    of the <Thread_Manager>.
{
friend class ACE_Thread_Manager;
public:
  // = Initialization method.
  ACE_Thread_Descriptor (void);

  // = Accessor methods.
  ACE_thread_t self (void);
  // Unique thread id.

  void self (ACE_hthread_t &);
  // Unique handle to thread (used by Win32 and AIX).

  int grp_id (void);
  // Group ID.

  ACE_Thread_State state (void);
  // Current state of the thread.

private:

  ACE_thread_t thr_id_;
  // Unique thread ID.
    
  ACE_hthread_t thr_handle_;
  // Unique handle to thread (used by Win32 and AIX).

  int grp_id_;
  // Group ID.

  ACE_Thread_State thr_state_;
  // Current state of the thread.
};

#if !defined (ACE_HAS_THREADS)

class ACE_Export ACE_Thread_Manager
{
public:
  enum
  {
    DEFAULT_SIZE = 100
  };

  ACE_Thread_Manager (int = 0) {}
  ~ACE_Thread_Manager (void) {}

  int open (size_t = DEFAULT_SIZE) { return -1; }
  int close (void) { return -1; }
  int spawn (ACE_THR_FUNC,
	     void * = 0,
	     long = 0, 
	     ACE_thread_t * = 0, 
	     ACE_hthread_t * = 0,
	     u_int = 0,
	     int = -1,
	     void * = 0, 
	     size_t = 0) { return -1;}
  int spawn_n (int, 
	       ACE_THR_FUNC, 
	       void * = 0, 
	       long = 0, 
	       u_int = 0,
	       int = -1) { return -1;}
  void *exit (void *) { return 0; }
  void wait (const ACE_Time_Value * = 0) {}
  int thread_descriptor (ACE_thread_t, ACE_Thread_Descriptor &) { return -1;}
  int hthread_descriptor (ACE_hthread_t, ACE_Thread_Descriptor &) { return -1;}
  int suspend_all (void) { return -1; }
  int suspend (ACE_thread_t) { return -1; }
  int suspend_grp (ACE_thread_t) { return -1; }
  int resume_all (void) { return -1; }
  int resume (ACE_thread_t) { return -1; }
  int resume_grp (ACE_thread_t) { return -1; }
  int kill_all (int) { return -1; }
  int kill (ACE_thread_t) { return -1; }
  int kill_grp (ACE_thread_t) { return -1; }
  int cancel_all (void) { return -1; }
  int cancel (int) { return -1; }
  int cancel_grp (int) { return -1; }
  void dump (void) const { }
};

class ACE_Export ACE_Thread_Control
{
public:
  ACE_Thread_Control (ACE_Thread_Manager * = 0, int = 0) {}
  ~ACE_Thread_Control (void) {}
  ACE_Thread_Manager *thr_mgr (void) { return 0; }
  ACE_Thread_Manager *thr_mgr (ACE_Thread_Manager *) { return 0; }
  void *exit (void *) { return 0; }
  int insert (ACE_Thread_Manager *) { return 0; }
  void *status (void *) { return 0; }
  void *status (void) { return 0; }
  void dump (void) const { }
};
#else

// Forward declaration.
class ACE_Thread_Control;

class ACE_Export ACE_Thread_Manager
  // = TITLE
  //    Manages a pool of threads.
  //
  // = DESCRIPTION
  //    This class allows operations on groups of threads atomically.
{
friend class ACE_Thread_Control;
public:
  enum
  {
    DEFAULT_SIZE = 100
  };

  // = Initialization and termination methods.
  ACE_Thread_Manager (size_t size = ACE_Thread_Manager::DEFAULT_SIZE);
  ~ACE_Thread_Manager (void);

  int open (size_t size = DEFAULT_SIZE); 
  // Initialize the manager with room for SIZE threads.

  int close (void);		
  // Release all resources.

  int spawn (ACE_THR_FUNC func, 
	     void *args = 0,
	     long flags = THR_NEW_LWP, 
	     ACE_thread_t * = 0, 
	     ACE_hthread_t *t_handle = 0,
	     u_int priority = 0,
	     int grp_id = -1,
	     void *stack = 0, 
	     size_t stack_size = 0);
  // Create a new thread, which executes <func>.  

  // Returns: on success a unique group id that can be used to control
  // other threads added to the same group.  On failure, returns -1.

  int spawn_n (int n, 
	       ACE_THR_FUNC func, 
	       void *args = 0,
	       long flags = THR_NEW_LWP,
	       u_int priority = 0,
	       int grp_id = -1);
  // Create N new threads, all of which execute <func>.  
  
  // Returns: on success a unique group id that can be used to control
  // all of the threads in the same group.  On failure, returns -1.

  void *exit (void *status, int do_thread_exit = 1);
  // Called to clean up when a thread exits.  If <do_thread_exit> is
  // non-0 then <ACE_Thread::exit> is called to exit the thread, in
  // which case <status> is passed as the exit value of the thread.

  int wait (const ACE_Time_Value *timeout = 0);	
  // Block until there are no more threads running in the
  // <Thread_Manager> or <timeout> expires.  Returns 0 on success and
  // -1 on failure.

  // = Accessors for <ACE_Thread_Descriptors>.
  int thread_descriptor (ACE_thread_t, ACE_Thread_Descriptor &);
  // Return the thread descriptor (indexed by ACE_thread_t).  Returns 0 on
  // success and -1 if not found.

  int hthread_descriptor (ACE_hthread_t, ACE_Thread_Descriptor &);
  // Return the thread descriptor (indexed by ACE_hthread_t).  Returns 0
  // on success and -1 if not found.

  int thr_self (ACE_hthread_t &);
  // Passes out the "real" handle to the thread, caching it if
  // necessary in TSS to speed up subsequent lookups.

  // = Suspend methods, which isn't supported on POSIX pthreads (will
  // not block).
  int suspend_all (void);
  // Suspend all threads 
  int suspend (ACE_thread_t);
  // Suspend a single thread.
  int suspend_grp (int grp_id);
  // Suspend a group of threads.
  int testsuspend (ACE_thread_t t_id);
  // True if <t_id> is inactive (i.e., suspended), else false.

  // = Resume methods, which isn't supported on POSIX pthreads (will
  // not block).
  int resume_all (void);
  // Resume all stopped threads 
  int resume (ACE_thread_t);
  // Resume a single thread.
  int resume_grp (int grp_id);
  // Resume a group of threads.
  int testresume (ACE_thread_t t_id);
  // True if <t_id> is active (i.e., resumed), else false.

  // = Kill methods, send signals -- which isn't supported on Win32
  // (will not block).
  int kill_all (int signum);
  // Send signum to all stopped threads 
  int kill (ACE_thread_t, int signum);
  // Kill a single thread.
  int kill_grp (int grp_id, int signum);
  // Kill a group of threads.

  // = Cancel methods, which provides a cooperative thread-termination
  // mechanism (will not block).
  int cancel_all (void);
  // Send signum to all stopped threads 
  int cancel (ACE_thread_t);
  // Cancel a single thread.
  int cancel_grp (int grp_id);
  // Cancel a group of threads.
  int testcancel (ACE_thread_t t_id);
  // True if <t_id> is cancelled, else false.

  // = Set/get group ids for a particular thread id.
  int set_grp (ACE_thread_t, int grp_id);
  int get_grp (ACE_thread_t, int &grp_id);

  void dump (void) const;
  // Dump the state of an object.

  ACE_ALLOC_HOOK_DECLARE;
  // Declare the dynamic allocation hooks.

private:
  int resize (size_t);
  // Resize the pool of Thread_Descriptors.

  int spawn_i (ACE_THR_FUNC func, 
	       void *args, 
	       long flags, 
	       ACE_thread_t * = 0, 
	       ACE_hthread_t *t_handle = 0,
	       u_int priority = 0,
	       int grp_id = -1,
	       void *stack = 0, 
	       size_t stack_size = 0);
  // Create a new thread (must be called with locks held).

  int find (ACE_thread_t t_id);
  // Locate the index of the table slot occupied by <t_id>.  Returns
  // -1 if <t_id> is not in the table doesn't contain <t_id>.

  int insert_thr (ACE_thread_t t_id, ACE_hthread_t, int grp_id = -1);
  // Insert a thread in the table (checks for duplicates).

  int append_thr (ACE_thread_t t_id, ACE_hthread_t, 
		  ACE_Thread_State,
		  int grp_id);
  // Append a thread in the table (adds at the end, growing the table
  // if necessary).

  void remove_thr (int i);	
  // Remove thread from the table. 

  int thread_descriptor_i (ACE_thread_t, ACE_Thread_Descriptor &);
  // Implements the lookup function for the <thread_descriptor>.  Note
  // that this version assumes that the lock is held.  We need this to
  // avoid intra-class method deadlock on systems that lack recursive
  // mutexes.

  int hthread_descriptor_i (ACE_hthread_t, ACE_Thread_Descriptor &);
  // Implements the lookup function for the <hthread_descriptor>.
  // Note that this version assumes that the lock is held.  We need
  // this to avoid intra-class method deadlock on systems that lack
  // recursive mutexes.

  // = The following four methods implement a simple scheme for
  // operating on a collection of threads atomically.

  typedef int (ACE_Thread_Manager::*THR_FUNC)(int, int);

  int check_state (ACE_Thread_State state, ACE_thread_t thread);
  // Efficiently check whether <thread> is in a particular <state>.
  // This call updates the TSS cache if possible to speed up
  // subsequent searches.

  int apply_grp (int grp_id, THR_FUNC, int = 0);
  // Apply <func> to all members of the table that match the <grp_id>.

  int apply_all (THR_FUNC, int = 0);
  // Apply <func> to all members of the table.

  int resume_thr (int i);
  // Resume the thread at index <i>.

  int suspend_thr (int i);
  // Suspend the thread at index <i>.

  int kill_thr (int i, int signum);
  // Send signal <signum> to the thread at index <i>.

  int cancel_thr (int i);
  // Set the cancellation flag for the thread at index <i>.

  ACE_Thread_Descriptor *thr_table_;
  // Vector that describes thread state within the Thread_Manager.

  size_t max_table_size_;
  // Maximum number of threads we can manage (should be dynamically
  // allocated).

  size_t current_count_;
  // Current number of threads we are managing.

  int grp_id_;
  // Keeps track of the next group id to assign.

  // = ACE_Thread_Mutex and condition variable for synchronizing
  // termination.
  ACE_Thread_Mutex lock_;
  ACE_Condition_Thread_Mutex zero_cond_;
};


class ACE_Export ACE_Thread_Control
  // = TITLE
  //     Used to keep track of a thread's activities within its entry
  //     point function.
{
public:
  ACE_Thread_Control (ACE_Thread_Manager *tm = 0, 
		      int insert = 0);
  // Initialize the thread control object.  If <insert> != 0, then
  // register the thread with the Thread_Manager.

  ~ACE_Thread_Control (void);
  // Implicitly kill the thread on exit and remove it from its
  // associated ThreadManager.

  void *exit (void *status);
  // Explicitly kill the thread on exit and remove it from its
  // associated <Thread_Manager>.

  int insert (ACE_Thread_Manager *tm);
  // Store the <Thread_Manager> and use it to register ourselves for
  // correct shutdown.

  ACE_Thread_Manager *thr_mgr (void);
  // Returns the current <Thread_Manager>.

  ACE_Thread_Manager *thr_mgr (ACE_Thread_Manager *);
  // Atomically set a new <Thread_Manager> and return the old
  // <Thread_Manager>.

  void *status (void *status);
  // Set the exit status (and return existing status).

  void *status (void);
  // Get the current exit status.

  void dump (void) const;
  // Dump the state of an object.

  ACE_ALLOC_HOOK_DECLARE;
  // Declare the dynamic allocation hooks.

private:
  ACE_Thread_Manager *tm_;
  // Pointer to the thread manager for this block of code.

  void *status_;
  // Keeps track of the exit status for the thread.
};

#if defined (__ACE_INLINE__)
#include "ace/Thread_Manager.i"
#endif /* __ACE_INLINE__ */

#endif /* !defined (ACE_HAS_THREADS) */
#endif /* ACE_THREAD_MANAGER_H */

