
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
char* datePlusMonth(char* hex, int monthPlus) {

	char* splitHex;
	char* result;
	char* resultAjax;
	int day, month, year, i, yearAdd, monthAdd;
	int data[2];
	char dayStr[10], monthStr[10], yearStr[10], tempDay[10], tempMonth[10];

	i = 0;
	
	splitHex=(char*)malloc(100);
	memset(splitHex, 0, 100);

	result=(char*)malloc(100);
	memset(result, 0, 100);

	resultAjax=(char*)malloc(100);
	memset(resultAjax, 0, 100);

	splitHex = (char *)strtok(hex, "..");

	while (splitHex != NULL) {
		switch (i) {
		case 0: day = atoi(splitHex);
			break;
		case 1: month = atoi(splitHex);
			break;
		case 2: year = atoi(splitHex);
			break;

		}
		splitHex = (char *)strtok(NULL, "..");
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

	// end date equal day click check - 1
	if (data[0] == 1) {
		data[0] = 31;

		if (data[1] == 1) {
			year -= 1;
		}

		data[1] -= 1;

		if (data[1] == 0) {
			data[1] = 12;
		}

		checkMonth(data, data[1], data[0], year);
	} else {
		data[0] -= 1;
	}

	itoa(data[0], dayStr, 10);
	itoa(data[1], monthStr, 10);
	itoa(year, yearStr, 10);

	strcpy(result, "");
	strcpy(resultAjax, "");

	if (strlen(dayStr) == 1) {
		strcpy(tempDay, "0");
		strcat(tempDay, dayStr);
		strcat(result, tempDay);
		strcat(resultAjax, tempDay);
	} else {
		strcat(result, dayStr);
		strcat(resultAjax, dayStr);
	}

	strcat(result, ".");

	if (strlen(monthStr) == 1) {
		strcpy(tempMonth, "0");
        strcat(tempMonth, monthStr);
		strcat(result, tempMonth);
		strcat(resultAjax, tempMonth);
	} else {
		strcat(result, monthStr);
		strcat(resultAjax, monthStr);
	}

	strcat(result, ".");
	strcat(result, yearStr);
	strcat(resultAjax, yearStr);

	lr_save_string(resultAjax, "EnsuranceEndDateAjax");

	free(resultAjax);
	free(splitHex);
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
			if (month==4 || month==6 || month==9 || month==11) {
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
