/*
 * Original code by Balazs Nadasdi (http://github.com/Yitsushi/)
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must
 * not claim that you wrote the original software. If you use this
 * software in a product, an acknowledgment in the product documentation
 * would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * ::::: Educational purpose :::::
 *
 * Simple C program to read a file and print hex value (like hexdump),
 * but print only printable characters on the right side
 * (we don't want to print newlines).
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGTH 16
#define BLOCK_SIZE 16

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("Error while opening the file");
    return -1;
  }

  int offset = 0;

  int ch;
  char line[LINE_LENGTH + 1];
  memset(line, 0, sizeof line);
  while ((ch = fgetc(fp)) != EOF) {
    if (offset > 0 && offset % (LINE_LENGTH * BLOCK_SIZE) == 0) {
      printf(" *** Block #%d\n", offset / (LINE_LENGTH * BLOCK_SIZE));
    }

    if (offset % LINE_LENGTH == 0) {
      printf("0x%08x   ", offset);
    }

    printf("%02x ", ch);

    if (isprint(ch)) {
      line[offset % LINE_LENGTH] = ch;
    } else {
      line[offset % LINE_LENGTH] = '.';
    }

    if (offset % LINE_LENGTH == LINE_LENGTH-1) {
      printf(" | %s\n", line);
      memset(line, 0, sizeof line);
    }
    offset++;
  }

  if (strlen(line) > 0) {
    for (int i = 0; i < LINE_LENGTH - strlen(line); i++) {
      printf("   ");
    }
    printf(" | %s\n", line);
  }

  fclose(fp);

  return 0;
}
