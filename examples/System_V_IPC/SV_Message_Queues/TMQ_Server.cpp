#include "ace/Signal.h"
// @(#)TMQ_Server.cpp	1.1	10/18/96

#include "ace/Typed_SV_Message_Queue.h"
#include "ace/Log_Msg.h"
#include "test.h"

// Must be global for signal Message...
ACE_Typed_SV_Message_Queue<Message_Data> msgque 
  (SRV_KEY, ACE_Typed_SV_Message_Queue<Message_Data>::ACE_CREATE);

void
SIGNAL_handler (int)
{
  if (msgque.remove () < 0)
    ACE_ERROR ((LM_ERROR, "%p\n%a", "msgque.recv", 1));
  ACE_OS::exit (0);
}

int 
main (void) 
{
  char *username = ACE_OS::cuserid (0);
  Message_Data msg_data ((int) ACE_OS::getpid (), username, "I received your message.");
  ACE_Typed_SV_Message<Message_Data> send_msg (msg_data, 0, msg_data.length ());
  ACE_Typed_SV_Message<Message_Data> recv_msg (SRV_ID);

  ACE_Sig_Action sig2 ((ACE_SignalHandler) SIGNAL_handler, SIGINT);

  for (;;)
    {
      if (msgque.recv (recv_msg) == -1)
	ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "msgque.recv"), 1);
      
      Message_Data &recv_msg_data = recv_msg.data ();

      cout << "a msg of length "
	   << recv_msg_data.length ()
	   << " sent from client " 
	   << recv_msg_data.pid () 
	   << " (user " 
	   << recv_msg_data.user () << "): " 
	   << recv_msg_data.text () << "\n";
      cout.flush ();

      send_msg.type (recv_msg_data.pid ());

      if (msgque.send (send_msg) < 0)
	ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "msgque.send"), 1);
    }

  /* NOTREACHED */
  return 0;
}

#if defined (ACE_TEMPLATES_REQUIRE_SPECIALIZATION)
template class ACE_Typed_SV_Message_Queue<Message_Data>;
template class ACE_Typed_SV_Message<Message_Data>;
#endif /* ACE_TEMPLATES_REQUIRE_SPECIALIZATION */
