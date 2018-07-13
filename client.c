/* doCircularnt - client */
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock;
  struct sockaddr_in server;
  int vector[5];
  int circular_matrix[4][4];

  printf("Enter 5 integers: ");
  for (int i=0;i<5;i++){
	scanf("%d",&vector[i]);
		  }

  /* create socket */
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("Could not create socket. Error");
  }

  /* prepare the sockaddr_in structure */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(8880);

  /* connect to remote server */
  if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("Connect failed. Error");
    return 1;
  }

  /* send data to server */
  if (send(sock, &vector, sizeof(vector), 0) < 0) {
    printf("Send failed. Error");
    return 1;
  }

  /* receive a reply from the server */
  if (recv(sock, &circular_matrix, sizeof(circular_matrix), 0) < 0) {
    puts("Receive failed. Error");
    return 0;
  }

  printf("Circular Matrix :\n");
  
  /* print circulant matrix received */
  for( int i = 0; i < 5; i++ ) {
    for( int j = 0; j < 5; j++ ) {
      printf( "%d ", circular_matrix[i][j] );
    }
    printf( "\n" );
  }

  /* close the socket */
  close(sock);

  return 0;
}