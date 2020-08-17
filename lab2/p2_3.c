#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	char *name;
	int lit;
	int mat;
	int sci;
}student;

typedef struct courseT {
	student* students;
	int numEnrolled;
}courseT;

int main(int argc, char **argv) {
	FILE *f1, *f2;
	f1 = fopen(argv[1], "r");
	f2 = fopen(argv[2], "w");
	while (1) {
		int num, li = 0, ma = 0, sc = 0;
		char clas[30];
		courseT c;
		fscanf(f1, " %s", clas);
		fscanf(f1, " %d", &num);
		c.students = (student*)malloc(num * sizeof(student));
		c.numEnrolled = num;
		for (int i = 0; i < num; i++) {
			c.students[i].name = (char*)malloc(30 * sizeof(char));
			fscanf(f1, " %s", c.students[i].name);
			fscanf(f1, " %d", &c.students[i].lit);
			fscanf(f1, " %d", &c.students[i].mat);
			fscanf(f1, " %d", &c.students[i].sci);
			li += c.students[i].lit;
			ma += c.students[i].mat;
			sc += c.students[i].sci;
		}
		fprintf(f2, "%s %d %d %d\n", clas, li / num, ma / num, sc / num);
		free(c.students);
		char buf[5];
		fscanf(f1, " %s", buf);
		if (feof(f1)) break;
	}
	fclose(f1);
	fclose(f2);
	return 0;
}