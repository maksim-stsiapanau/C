
/*

Remove white spaces from string

Parameters:
input - source string

Output:

output - string without white spaces

*/
char* removeSpaces(char* input) {


	int i,j;

	char *output;

	output = input;

	for(i = 0, j = 0; i < strlen(input); i++, j++) {

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

char* subString(char* input, int offset, int len, char* output) {


	int input_len = strlen(input);

	if (offset + len > input_len) {

		return NULL;

	}

	strncpy(output, input + offset, len);

	return output;

}

/*

Parameters:
option - what do
additionalOpetion - offset for numbers between 0 - 9, for other set 0

Output:
character

Usage: 
0 - small russian letters
1 - big russian letters
2 - numbers [0,9] - additionalOption = 10
3 - numbers [1,9] - additionalOption = 10
4 - big english letters
5 - small english letters

*/
char generateSymbol(int option, int additionalOption) {


	switch (option) {
	
		case 0: 
	
			return (char)(rand()%32+224);
	
			break;
	
		case 1: 
	
			return (char)(rand()%32+192);
	
			break;
	
		case 2: 
	
			return (char)(rand()%additionalOption+48);
	
			break;
	
		case 3: 
	
			return (char)(rand()%(additionalOption-1)+49);
	
			break;

		case 4: 
	
			return (char)(rand()%26+65);
	
			break;

		case 5: 
	
			return (char)(rand()%26+97);
	
			break;

		default:
	
			return 100;
	
			break;

	}


}

/*
Convert hex to string

Parameters:
hex - source hex string

Output:
result - string

Usage:
hex to string
char *str;
str = convertHexToString("\xC7\xE0\xFF\xE2\xEA\xE0 \xE2 \xE4\xE0\xED\xED\xFB\xE9 \xEC\xEE\xEC\xE5\xED\xF2 \xE7\xE0\xED\xFF\xF2\xE0 \xE4\xF0\xF3\xE3\xE8\xEC \xEF\xEE\xEB\xFC\xE7\xEE\xE2\xE0\xF2\xE5\xEB\xE5\xEC");
*/

char* convertHexToString(char* hex) {

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

	Date plus month

	Parameters:
	date - start date
	monthPlus - count month plus to start date

	Output:

	result - date with offset

	Usage:
	char* date;

	date = (char*)malloc(100);

	memset(date, 0, 100);

    strcpy(date,"01.01.2012");

	datePlusMonth(date, 1);

*/
char* datePlusMonth(char* date, int monthPlus) {

	char* split;

	char* result;

	int day, month, year, i, yearAdd, monthAdd;

	int data[2];

	char dayStr[10], monthStr[10], yearStr[10], tempDay[10], tempMonth[10];

	i = 0;
	
	split=(char*)malloc(100);

	memset(split, 0, 100);

	result=(char*)malloc(100);

	memset(result, 0, 100);

	split = (char *)strtok(date, "..");

	while (split != NULL) {


		switch (i) {
		case 0: day = atoi(split);
			break;
		case 1: month = atoi(split);
			break;
		case 2: year = atoi(split);
			break;

		}

		split = (char *)strtok(NULL, "..");

		i++;


	}

	if (monthPlus % 12 == 0) {

		year += monthPlus / 12;

		checkMonth(data, month, day, year);


	} else {


		if (monthPlus < 12) {
		
			month = month + monthPlus;
		
			if (month > 12) {
		
				year = year + 1;
		
				month = month - 12;
		
			}
	
			checkMonth(data, month, day, year);
	
	
	
		} else {
	
			yearAdd  = monthPlus / 12;
	
			monthAdd = monthPlus % 12;
	
			year += yearAdd;
	
			month += monthAdd;

			checkMonth(data, month, day, year);
	
		}


	}


	itoa(data[0], dayStr, 10);

	itoa(data[1], monthStr, 10);

	itoa(year, yearStr, 10);

	strcpy(result, "");

	if (strlen(dayStr) == 1) {

		strcpy(tempDay, "0");

		strcat(tempDay, dayStr);

		strcat(result, tempDay);

	} else {

		strcat(result, dayStr);

	}

	strcat(result, ".");

	if (strlen(monthStr) == 1) {

		strcpy(tempMonth, "0");

        strcat(tempMonth, monthStr);

		strcat(result, tempMonth);

	} else {

		strcat(result, monthStr);

	}

	strcat(result, ".");

	strcat(result, yearStr);

	free(split);

	return result;

}

/*
	Check month boundaries

	Parameters:
	data - output array
	month - month for check
	day - day for check
	year - year for check
*/
void checkMonth(int data[], int month, int day, int year){

	if (month == 2) {


			switch (day) {
			
			case 29:

				if (!checkLeap(year)) {

					day = 28;

				}

				break;

			case 30:
				if (!checkLeap(year)) {

					day = 28;


				} else {

					day = 29;

				}

				break;

			case 31: 
				if (!checkLeap(year)) {

					day = 28;

				} else {

					day = 29;

				}
				break;

			}
			

		} else {

			if (day == 31) {
			
				if (month % 2 == 0 && month != 8 && month != 12) {

					day = 30;

				} 


            }

		}


		data[0] = day;

		data[1] = month;


}



/*
	Check leap year

	Parameters:
	year - year for check

	Output:
	result - 1 true; 0 - false
*/
int checkLeap(int year) {

	int result;

	if ((year % 4 == 0 && year % 100 !=0) || year % 400 == 0) {

		result  = 1;

	} else {

		result = 0;

	}

	return result;

}


/*

	Generating random string

	Parameters:
	length - string's length
	lang - language

	Output:
	result -  random string
*/
char* generateStr(int length, int lang) {

	int i;

    char* result;
	result=(char*)malloc(100);
	memset(result, 0, 100);


	// 1 - russian; 2- english; 3 - for bank cards
	switch (lang) {
	
		case 1:
	
			result[0]=generateSymbol(1, 0);
	
			for (i=1; i<length; i++) result[i]=generateSymbol(0, 0);
	
			break;

		case 2:
	
			result[0]=generateSymbol(4, 0);
	
			for (i=1; i<length; i++) result[i]=generateSymbol(5, 0);
	
			break;

		case 3:

			result[0]=generateSymbol(4, 0);

			for (i=1; i<length; i++) result[i]=generateSymbol(4, 0);

			break;

	}



	return result;
}

/*

	Generating random number

	Parameters:
	length - number's length

	Output:
	result - random number
*/
char* generateNumber(int length) {

	int i;

     char* result;
	result=(char*)malloc(100);
	
	memset(result, 0, 100);

	for (i=0; i<length; i++) result[i]=generateSymbol(2, 10);

	return result;
}


/*

	Convert string to hex

	Parameter:
	name - source string

	Output:
	hexString - result hex string
*/
char* convertStringToHex(char* name) {

	char* result;

	int i, j, k, l, dec, temp, t;

	int* numbers;

	char hexadec[100], hexString[1024];

	strcpy(hexString, "");

	l = strlen(name);

	i = 0;

	j = 1;

	t = 0;
	

	result = (char*)malloc(100);

	memset(result, 0, 100);

	numbers = (int*)malloc(l*4);

	memset(numbers, 0, l*4);


	while(name[i]) {

		
		if(name[i] < 0) {

			dec = name[i] + 256;

		} else {

			dec = name[i];

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


		strcat(hexString, "\\\\x");

		for (k= j-1; k>0; k--) {
			
            result[t] = hexadec[k];

			t++;
		}

		strcat(hexString, result);

		free(hexadec);

		j = 1;
        
		i++;

	}

	free(numbers);

	free(result);

	return hexString;
}