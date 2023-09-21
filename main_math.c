#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

// your include

int main() {
  double a, b;
  int flag;

  void *handle1;
  int (*add_i)(int , int );
  char *error_i;

  void *handle2;
  double (*add_d)(double, double);
  char *error_d;

  handle1 = dlopen("./math_i.so", RTLD_LAZY);
  if (!handle1)
  {
	fprintf(stderr, "%s\n", dlerror());
	exit(0);
  }
 
  handle2 = dlopen("./math_d.so", RTLD_LAZY);
  if (!handle2)
  {
	  fprintf(stderr, "%s\n", dlerror());
	  exit(0);
  }

  add_i = dlsym(handle1, "add_i");
  if ((error_i = dlerror()) != NULL)
  {
	  fprintf(stderr, "%s\n", error_i);
	  exit(1);
  }

  add_d = dlsym(handle2, "add_d");
  if ((error_d = dlerror()) != NULL)
  {
	  fprintf(stderr, "%s\n", error_d);
	  exit(1);
  }

  printf("Enter the value of a: ");
  scanf("%lf", &a);

  printf("Enter the value of b: ");
  scanf("%lf", &b);

  printf("Press 0 to compute as double, 1 as int: ");
  scanf("%d", &flag);

  printf("a = %f\nb = %f\nflag = %d\n", a,b,flag);
  if (flag)
  {	printf("The sum of the two integers is %d\n", add_i(a,b));	}
  else
  {	printf("The sum of the two doubles is %f\n", add_d(a,b));	}


  if (dlclose(handle1) < 0)
  {
	  fprintf(stderr, "%s\n", dlerror());
	  exit(1);
  }

  if (dlclose(handle2) < 0)
  {
	  fprintf(stderr, "%s\n", dlerror());
	  exit(1);
  }

  return 0;
}
