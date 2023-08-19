#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dmessage.pb-c.h"

int main (int argc, const char * argv[])
{
  DMessage msg = DMESSAGE__INIT;  // DMessage (repeated string)
  void *buf;                      // Buffer to store serialized data
  unsigned len,i,j;               // Length of serialized data

  msg.n_d = argc - 1;                      // Save number of repeated strings
  msg.d = malloc (sizeof (char*) * msg.n_d);   // Allocate memory to store strings
  for (j = 0; j < msg.n_d; j++) {
      msg.d[j] = (char*)argv[j+1];         // Access msg.c[] as array
  }
  len = dmessage__get_packed_size (&msg);  // This is calculated packing length
  buf = malloc (len);                      // Allocate required serialized buffer length
  dmessage__pack (&msg, buf);              // Pack the data

  fprintf(stderr,"Writing %d serialized bytes\n",len); // See the length of message
  fwrite (buf, len, 1, stdout);            // Write to stdout to allow direct command line piping

  free (msg.d); // Free storage for repeated string
  free (buf);   // Free serialized buffer
  return 0;
}
