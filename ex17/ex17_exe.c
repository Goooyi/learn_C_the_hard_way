#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROW 100

void handle_error(char *msg){
  printf("%s", msg);
  printf("Error %s", errno);
  exit(1);
}
// 2 Address
struct Address {
  char name[MAX_DATA];
  char addr[MAX_DATA];
};

struct Database {
  struct Address row[MAX_ROW];
  int set[MAX_ROW];
};

struct Conn {
  FILE *file;
  struct Database *db;
};


void open_file(char *file_name, struct Conn *conn, char mode) {
  FILE *tmp = NULL;
  if (mode == 'c') {
    tmp = fopen(file_name, "w");
  } else {
    tmp = fopen(file_name, "r+");
  }
  if (tmp == NULL) {
    handle_error("Failed to open file");
  }

  conn->file = tmp;
}


void load_db(struct Conn *conn){
  if (conn->file == NULL) {
    printf("FIle not open yet");
    exit(1);
  }
  fread(conn->db, sizeof(struct Database), 1, conn->file);
}

struct Conn* create_db(char *file_name) {
  struct Conn *conn = malloc(sizeof(struct Conn));
  if(conn == NULL) {
    handle_error("malloc wrong");
  }
  conn->db = malloc(sizeof(struct Database));
  if (conn->db == NULL) {
    handle_error("malloc wrong");
  }
  open_file(file_name, conn, 'c');

  return conn;
}

void set_addr(struct Conn *conn, char* name,struct Address addr) {
  int i = 0;
  while(i < MAX_ROW) {
    if (conn->db->set[i] == 0) {
      conn->db->row[i] = addr;
      break;
    }
    i++;
  }
  if (i == MAX_ROW) {
    handle_error("NO ROOM for new data");
  }
}

int main(int argc, char *argv[]) {
  if (argc == 3) {
    if (argv[1][0] != 'c') {
      handle_error("wrong argument");
    }
    struct Conn *conn = create_db(argv[2]);
  } else if (argc == 5) {
    if (argv[1][0] == 'c') {
      struct Conn *conn = open_file(argv[2]);
      load_db(conn);
    }
    set_addr(conn, argv[3], argv[4]); // how to load addr string
  }

  return 0;
}