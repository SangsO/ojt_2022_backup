#include <stdlib.h>
#include <string.h>
#include "series.h"

slices_t slices(char *input_text, unsigned int substring_length) {
   slices_t res;
   memset(&res, 0, sizeof(slices_t));
   unsigned int input_len = strlen(input_text);

   if (substring_length == 0 || substring_length > input_len) {
      return res;
   }

   unsigned int num_slices = input_len - substring_length + 1;
   res.substring = (char **) malloc(sizeof(char *) * num_slices);

   for (unsigned int i = 0; i < num_slices; i++) {

      char *new_str = (char *) malloc(sizeof(char) * (substring_length + 1));
      strncpy(new_str, &input_text[i], substring_length);
      new_str[substring_length] = '\0';
      res.substring_count += 1;
      res.substring[i] = new_str;
   }

   return res;
}