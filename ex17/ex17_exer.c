// TODO
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 100
#define MAX_DATA 512

// define needed strtuctuers
// TODO: struct name vs typedef name
typedef struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
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
  // TODO why this if else?
  if (errno) {
    perror(err_msg);
  } else {
    printf("Error %s", err_msg);
  }
  exit(1);
}

// TODO
void address_print(Address *addr) { printf("%s, %s", addr->name, addr->email); }

void database_load(Connection *conn) {
  int rc = fread(conn->db, sizeof(Database), 1, conn->file);
  if (rc != 1) {
    printf("Error loading");
  }
}

// database_open()
// TODO
Connection *database_open(const char *filename, char mode) {
  Connection *conn = malloc(sizeof(Connection));
  if (!conn) {
    die("Memory error");
  }
  conn->db = malloc(sizeof(Database));
  if (!conn->db) {
    die("Memory error");
  }

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    // TODO: diff between `r` and `r+`
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      database_load(conn);
    }
  }

  // TODO: need to check whether fopen successed!!
  if (!conn->file) {
    die("Failed to open the file");
  }

  return conn;
}

// close a file and free memory
void database_close(Connection *conn) {
  if (conn) {
    if (conn->file) {
      fclose(conn->file);
    }
    if (conn->db) {
      free(conn->db);
    }
    free(conn);
  }
}

void database_write(Connection *conn) {
  // TODO what does `rewind()` do?
  if (conn->db) {
    int rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
    if (rc != 1) {
      die("can not write");
    }
    rc = fflush(conn->file);
    if (rc != 1) {
      die("Can not flush");
    }
  } else {
    die("connection's database is empty");
    return;
  }
}

// TODO: create a cono or db??? what is the purpose
void database_create(Connection *conn) {
}

// set in database
// TODO: why pass `const char *` instead `char *` here?
void database_set(int idx, Connection *conn, const char *name, const char *email) {
  if (conn->db->rows[idx].set != 0) {
    printf("data not empty, overwrite");
  }
  conn->db->rows[idx].set = 1;
  // TODO: copy string in C??
  strcpy(conn->db->rows[idx].email, email);
  strcpy(conn->db->rows[idx].name, name);
  // TODO: cation like strncpy?
}

// delete in database
int database_delete(Connection *conn, int idx) {
  // TODO: The author created a new addr instead of just set, wht?
  conn->db->rows[idx].set = 0;
}

// TODO
void database_list() {}

// main() func to test
int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: ex17_exer <dbfile> <action> [action params]");
  } else {
    char *filename = argv[1];
    char action = argv[2][0];
    Connection *conn = database_open(filename, action);

    switch (action) {
      case 'c':
        database_create(conn);
    }
  }
}