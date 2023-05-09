#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person{
	char* name;
	int age;
	int height;
	int weight;
};

struct Person* create_Person(char* name, int age, int height, int weight){
	struct Person* who = malloc(sizeof(struct Person));
	assert(who != NULL);

	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void destroy_Person(struct Person* who){
	assert(who != NULL);

	free(who->name);
	free(who);
}

void print_Person(struct Person* who){
	assert(who != NULL);

	printf("My name is %s, age is %d, height is %d, weight is %d.\n", who->name, who->age, who->height, who->weight);
}

int main(int argc, char* argv[])
{
	struct Person* p1 = create_Person("lisi", 18, 2, 60);
	struct Person* p2 = create_Person("zhangsan", 23, 2, 80);

	printf("P1 is at memory location %p:\n", p1);
	print_Person(p1);
	printf("P2 is at memory location %p:\n", p2);
	print_Person(p2);

	// print_Person(NULL); break the code

	destroy_Person(p1);
	destroy_Person(p2);

	return 0;
}
