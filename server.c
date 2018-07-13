
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
  int server_sock, client_sock, c, read_size;
  struct sockaddr_in server, client;
  int received_vector[5];
  int circular_matrix[5][5];
  
  /* create socket */
  server_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (server_sock == -1) {
    printf("Could not create socket. Error");
  }

  /* prepare the sockaddr_in structure */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8880);

  /* bind the socket */
  if (bind(server_sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("Bind failed. Error");
    return 1;
  }

  /* Listen for connection */
  listen(server_sock, 3);

  c = sizeof(struct sockaddr_in);

  /* accept connection from an incoming client */
  client_sock = accept(server_sock, (struct sockaddr*)&client, (socklen_t*)&c);
  if (client_sock < 0) {
    perror("Accept failed. Error");
    return 1;
  }

  /* receive a message from client */
  while ((read_size = recv(client_sock, &received_vector, sizeof(received_vector), 0)) > 0) {
    printf("Two Dimensional array elements:\n");

    /* DO CIRCULANT */
   
	  for(int i=0; i<5; i++)
        {
		
                for(int j=0;j<5;j++)
                {
                    circular_matrix[i][j]=received_vector[j];
                }
                int temp=received_vector[4];
                for(int x=4;x>0;x--)
                {
                    received_vector[x]=received_vector[x-1];
                }
                received_vector[0]=temp;
        }

	//send(sockfd,&circular_matrix,sizeof(circular_matrix),0);
	  
	  
    /* ! End OF DO CIRCULANT */

    /* print circulant matrix generated */
    for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
        printf("%d ", circular_matrix[i][j]);
      }
      printf("\n");
    }

    printf("\n");

    /* send circulant matrix back to client */
    if (send(client_sock, &circular_matrix, sizeof(circular_matrix), 0) < 0) {
      perror("Send failed. Error");
    return 1;
    }
  }

  /* print on connection termination */
  if (read_size == 0) {
      printf("Client disconnected. Success");
  }
  else if (read_size == -1) {
      perror("Receive failed. Error");
  }

  return 0;
}