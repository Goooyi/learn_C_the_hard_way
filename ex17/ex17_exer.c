// TODO
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 100
#define MAX_DATA 512

// define needed strtuctuers
// TODO: struct name vs typedef name
typedef struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
  void *some_data = malloc(MAX_DATA * sizeof(char));
} Address;

typedef struct Database {
  Address rows[MAX_ROW];
} Database;

typedef struct Connection {
  // TODO what is file
  FILE *file;
  Database *db;
} Connection;

void die(const char *err_msg) {
  // why this if else?
  if (errno) {
    perror(err_msg);
  } else {
    printf("Error %s", err_msg);
  }
  exit(1);
}

// TODO
// address print
void address_print(Address &addr) {
  if (addr->set != 1) {
    printf("address %l not set", addr->);
  } else {
    printf("%s, %s", addr->name, addr->email);
  }
}

void database_load(Connection &conn) {
  // TODO: nullptr??
  if (conn->db == NULL || conn->file == NULL) {
    printf("Null pointer");
  }

  // TODO: how to read the file? what is the format?
  int rc = fread(conn->db, sizeof(database), 1, conn->file);
  if (rc != 1) {
    printf("Error loading");
  }
}

// database_open()
// TODO： ？？ what to do?
void database_open(FILE &f) {
  if (f == NULL) {
    printf("Null file pointer");
  }

  Database *db = malloc(sizeof(Database));
  if (db == NULL) {
    printf("create db error");
  }
  Connection *conn = malloc(sizeof(Connection));
  conn->file = f;
  conn->db = db;
}

// close a file and free memory
int database_close(conn *connection) {
  if (check_nullptr(connection) == -1) {
    return -1;
  }
  free(connection->db);
  close(connection->files);

  return 1;
}

// write in database
int database_write(Address *cur_add, db *cur_db) {
  if (check_nullptr(cur_db) == -1 or check_nullptr(cur_add) == -1) {
    return -1;
  }
  cur_db->cur_s += 1;
  // TOOD: should deep copy?
  cur_db->addr[cur_db->cur_s] = cur_add;
}

// set in database
// TODO:wtf is the difference

// create in database
// TODO: create a cono or db???
int database_create() {}

void database_set()

    // get in database
    int database_get(db &cur_db, int idx) {
  check_nullptr(cur_db);
  if (idx > MAX_ROW) {
    printf("index out of bound");
    // TODO
    exit(1);
  }
  printf("User: %s %s with some data: %s", cur_db->addr->last_name,
         cur_db->addr->first_name, cur_db->addr->some_data)
}

// delete in database
int database_delete(db &cur_db) {
  check_nullptr(cur_db);
  for (int i = 0; i < cur_db.cur_s; i++) {
    free(cur_db->addr->some_data);
    // TODO: DO I need to do this?
    cur_db->addr = NULL;
  }
}
// list print a database
void database_list() {}

// main() func to test