/*
merge  two string to one
*/
char* merge_two_string(char* first_str, char* second_string) {

	char* result;
	int len_first, len_second, len_result;

	len_first = strlen(first_str);
	len_second = strlen(second_string);
	len_result = len_first + len_second + 2;

	result = (char*)malloc(len_result);
	memset(result,0, len_result);

	sprintf(result, "%s_%s", first_str, second_string);
	return result;
}


/*

Remove white spaces from string

Parameters:
input - source string

Output:

output - string without white spaces

*/
char* remove_spaces(char* input) {

	int i,j, len;
	char *output;

	len = strlen(input);

	output = (char*)malloc(len + 1);
	memset(output,0,len + 1);

	strcpy(output,input);

	for(i = 0, j = 0; i < len; i++, j++) {
		if (input[i] != ' ') {
			output[j] = input[i];
		} else {
			j--;
		}
	}

	output[j] = 0;
	return output;
}

/*
  
  Substring string

  Parameters:
  input - source string
  offset - start point
  len - length for sub string
  output - result string

  Output:

  result - sub string  
 */

char* sub_string(char* input_str, int offset, int len) {

	char* output;

	int input_str_len = strlen(input_str);

	output = (char*)malloc(input_str_len + 1);
	memset(output,0,input_str_len + 1);

	if (offset + len > input_str_len) {
		return NULL;
	}

	strncpy(output, input_str + offset, len);
	return output;
}




// ----------------------------------------------------------------------------
//
// Description:
//    Search for and replace text within a string.
//
// Parameters:
//    src (in) - pointer to source string
//    from (in) - pointer to search text
//    to (in) - pointer to replacement text
//
// Returns:
//    Returns a pointer to dynamically-allocated memory containing string
//    with occurences of the text pointed to by 'from' replaced by with
//    the text pointed to by 'to'.
//
// Notes:
//    Do not use this directly in scripts unless you are a more advanced
//    user who knows C and string handling. See below for the function you
//    should use!
//
// ----------------------------------------------------------------------------
char *strReplace(const char *src, const char *from, const char *to)
{
  char *value;
  char *dst;
  char *match;
  int size;
  int fromlen;
  int tolen;

  // Find out the lengths of the source string, text to replace, and
  // the replacement text.
  size = strlen(src) + 1;
  fromlen = strlen(from);
  tolen = strlen(to);

  // Allocate the first chunk with enough for the original string.
  value = (char *)malloc(size);

  // We need to return 'value', so let's make a copy to mess around with.
  dst = value;

  // Before we begin, let's see if malloc was successful.
  if ( value != NULL )
  {
    // Loop until no matches are found.
    for ( ;; )
    {
      // Try to find the search text.
      match = (char *) strstr(src, from);
      if ( match != NULL )
      {
        // Found search text at location 'match'.
        // Find out how many characters to copy up to the 'match'.
        size_t count = match - src;

        // We are going to realloc, and for that we will need a
        // temporary pointer for safe usage.
        char *temp;

        // Calculate the total size the string will be after the
        // replacement is performed.
        size += tolen - fromlen;

        // Attempt to realloc memory for the new size.
        //
        // temp = realloc(value, size);
        temp = (char *)realloc(value, size);

        if ( temp == NULL )
        {
          // Attempt to realloc failed. Free the previously malloc'd
          // memory and return with our tail between our legs.
          free(value);
          return NULL;
        }

        // The call to realloc was successful. But we'll want to
        // return 'value' eventually, so let's point it to the memory
        // that we are now working with. And let's not forget to point
        // to the right location in the destination as well.
        dst = temp + (dst - value);
        value = temp;

        // Copy from the source to the point where we matched. Then
        // move the source pointer ahead by the amount we copied. And
        // move the destination pointer ahead by the same amount.
        memmove(dst, src, count);
        src += count;
        dst += count;

        // Now copy in the replacement text 'to' at the position of
        // the match. Adjust the source pointer by the text we replaced.
        // Adjust the destination pointer by the amount of replacement
        // text.
        memmove(dst, to, tolen);
        src += fromlen;
        dst += tolen;
      }
      else // No match found.
      {
        // Copy any remaining part of the string. This includes the null
        // termination character.
        strcpy(dst, src);
        break;
      }
    } // For Loop()
  }
  return value;
}

/* 
	Parse hex to string
	char *str;
	str = convert_hex_to_str("\xC7\xE0\xFF\xE2\xEA\xE0 \xE2 \xE4\xE0\xED\xED\xFB\xE9 \xEC\xEE\xEC\xE5\xED\xF2 \xE7\xE0\xED\xFF\xF2\xE0 \xE4\xF0\xF3\xE3\xE8\xEC \xEF\xEE\xEB\xFC\xE7\xEE\xE2\xE0\xF2\xE5\xEB\xE5\xEC");
	lr_output_message("%s", str);
*/

char* convert_hex_to_str(char* hex) {

	char* splitHex;
	char* result;
	
	splitHex=(char*)malloc(100);
	memset(splitHex, 0, 100);

	result=(char*)malloc(100);
	memset(result, 0, 100);

	splitHex = (char *)strtok(hex, ".\\x");

	while (splitHex != NULL) {
		result = splitHex;
        splitHex = (char *)strtok(NULL, ".\\x");

	}

	free(splitHex);
	return result;
}

/*
	Convert string to hex

*/
char* convert_str_to_hex(char* name) {

	char* result, *hexadec, *hex_string;
	int j, k, dec, temp, t;

	hex_string = (char*)malloc(1024);
	memset(hex_string, 0, 1024);

	strcpy(hex_string, "");

	while(*name) {
		j = 1;
		t = 0;

		result = (char*)malloc(100);
		memset(result, 0, 100);

		hexadec = (char*)malloc(100);
		memset(hexadec, 0, 100);

		if(*name < 0) {
			dec = *name + 256;
		} else {
			dec = *name;
		}

		while (dec != 0) {
			temp = dec % 16;
			if (temp < 10) {
				temp = temp + 48;
			} else {
				temp = temp + 55;
			}
            hexadec[j++] = temp;
			dec = dec / 16;
		}

		strcat(hex_string, "\\\\x");

		for (k= j-1; k>0; k--) {
            result[t] = hexadec[k];
			t++;
		}

		strcat(hex_string, result);
		free(hexadec);
		free(result);
		name +=1;
	}

	return hex_string;
}
