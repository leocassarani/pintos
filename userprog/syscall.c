#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
static void syscall_exit (int);
static int syscall_write (int, const void *, unsigned);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  int syscall_nr = *(int *) f->esp;

  switch (syscall_nr)
    {
    case SYS_EXIT:
      {
        int status = *((int *) f->esp + 1);
        syscall_exit (status);
      }
    case SYS_WRITE:
      {
        int fd = *((int *) f->esp + 1);
        const void *buffer = *((void **) f->esp + 2);
        unsigned size = *((unsigned *) f->esp + 3);
        f->eax = syscall_write (fd, buffer, size);
      }
    }
}

static void
syscall_exit (int status)
{
  printf("%s: exit(%d)\n", thread_current ()->name, status);
  thread_exit ();
}

static int
syscall_write (int fd, const void *buffer, unsigned size)
{
  if (fd == STDOUT_FILENO)
    putbuf (buffer, size);

  return size;
}
