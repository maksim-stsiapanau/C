/*

Parameters:
option - what do
additionalOpetion - offset for numbers between 0 - 9, for other set 0

Output:
character

Usage: 
0 - small russian letters
1 - big russian letters
2 - numbers [0,9] - additional_option = 10
3 - numbers [1,9] - additional_option = 10
4 - big english letters
5 - small english letters

*/
char generate_symbol(int option, int additional_option) {


	switch (option) {
		case 0: 
			return (char)(rand()%32+224);
			break;
		case 1: 
			return (char)(rand()%32+192);
			break;
		case 2: 
			return (char)(rand()%additional_option+48);
			break;
		case 3: 
			return (char)(rand()%(additional_option-1)+49);
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

char* generate_name(int length, int lang) {

	int i;

    char* result;
	result=(char*)malloc(100);
	memset(result, 0, 100);


	// 1 - russian; 2- english; 3 - for bank cards
	switch (lang) {
		case 1:
			result[0]=generate_symbol(1, 0);
			for (i=1; i<length; i++) result[i]=generate_symbol(0, 0);
			break;

		case 2:
			result[0]=generate_symbol(4, 0);
			for (i=1; i<length; i++) result[i]=generate_symbol(5, 0);
			break;

		case 3:
			result[0]=generate_symbol(4, 0);
			for (i=1; i<length; i++) result[i]=generate_symbol(4, 0);
			break;
	}
	return result;
}

char* generate_number(int length) {

	int i;

    char* result;

	result=(char*)malloc(100);
	memset(result, 0, 100);

	for (i=0; i<length; i++) result[i]=generate_symbol(2, 10);
	return result;
}


/*SNILS*/
typedef struct {
	char* first_three_number;
	char* second_three_number;
	char* third_three_number;
	char* control_number;
} snils;


//destroy snils object
void free_struct_snils(snils *sn) {

	free(sn->first_three_number);
	free(sn->second_three_number);
	free(sn->third_three_number);
	free(sn->control_number);

	sn->first_three_number = NULL;
	sn->second_three_number = NULL;
	sn->third_three_number = NULL;
	sn->control_number = NULL;
}

/*
Generating control number for snils
*/

char* get_control_num(int control_sum) {

	char* control_number;
	int i;

	control_number = (char*)malloc(100);
	memset(control_number,0,100);

	if (control_sum < 100) {
		if (control_sum < 10) {
			sprintf(control_number,"0%d",control_sum);
		} else {
			itoa(control_sum, control_number,10);
		}
	}

	if (control_sum == 100 || control_sum == 101) {
		sprintf(control_number,"%d%d",0,0);
	}

	if (control_sum > 101) {
		control_number = get_control_num(control_sum%101);
	}

	return control_number;
}

/*
Generating snils
*/
snils generate_snils_control_number() {

	int control_sum = 0, i;
	char* control_number;
	snils sn;
	char* first_three_number = generate_number(3);
	char* second_three_number = generate_number(3);
	char* third_three_number = generate_number(3);

	sn.first_three_number = (char*)malloc(strlen(first_three_number) + 1);
	memset(sn.first_three_number, 0, strlen(first_three_number) + 1);
	strcpy(sn.first_three_number, first_three_number);

	sn.second_three_number = (char*)malloc(strlen(second_three_number) + 1);
	memset(sn.second_three_number, 0, strlen(second_three_number) + 1);
	strcpy(sn.second_three_number, second_three_number);

	sn.third_three_number = (char*)malloc(strlen(third_three_number) + 1);
	memset(sn.third_three_number, 0, strlen(third_three_number) + 1);
	strcpy(sn.third_three_number, third_three_number);

	for (i=0; i<3; i++) {
		control_sum += (*first_three_number - '0') * (9 - i);
		control_sum += (*second_three_number - '0') * (6 - i);
		control_sum += (*third_three_number - '0') * (3 - i);
		first_three_number += 1;
		second_three_number += 1;
		third_three_number += 1;
	}

	control_number = get_control_num(control_sum);

	sn.control_number = (char*)malloc(strlen(control_number) + 1);
	memset(sn.control_number, 0, strlen(control_number) + 1);
	strcpy(sn.control_number, control_number);

	free(first_three_number);
	free(second_three_number);
	free(third_three_number);
	free(control_number);

	return sn;
}


/*
	Generating inn legal
*/
char* generate_inn_legal()
{
	int x_digit, i;

	long x_checksum;

	char* x_retval;

    
	int mask[9] =  {2,4,10,3,5,9,4,6,8};

	x_retval = (char*)malloc(10);
	memset(x_retval,0,10);

	for (i=0; i < 9; i++) {
		if (i == 0) {
				x_digit = rand() % 10;
				x_checksum = x_digit*mask[i];
				sprintf(x_retval, "%s%d", x_retval, x_digit);
			} else {
				x_digit = rand() % 10;
				x_checksum = x_checksum + x_digit*mask[i];
				sprintf(x_retval, "%s%d", x_retval, x_digit);
			}
	}

	if (x_checksum%11 == 10) x_checksum = 0;
		else x_checksum = x_checksum%11;

	sprintf(x_retval, "%s%d", x_retval, x_checksum);
	return x_retval;
}

/*
	Generating inn physics

*/
char* generate_inn_physics()
{
	int x_digit, i;
	long x_checksum1;
	long x_checksum2;
	char* x_retval;
	int mask1[10] =  {7,2,4,10,3,5,9,4,6,8};
	int mask2[11] =  {3,7,2,4,10,3,5,9,4,6,8};

	x_retval = (char*)malloc(13);
	memset(x_retval,0,13);

	for (i=0; i < 10; i++) {
		if (i == 0) {
			x_digit = (rand() % 9) + 1;
			x_checksum1 = x_digit*mask1[i];
			x_checksum2 = x_digit*mask2[i];
			sprintf(x_retval, "%s%d", x_retval, x_digit);
		} else {
			x_digit = rand() % 10;
			x_checksum1 = x_checksum1 + x_digit*mask1[i];
			x_checksum2 = x_checksum2 + x_digit*mask2[i];
			sprintf(x_retval, "%s%d", x_retval, x_digit);
		}
	}

	if (x_checksum1%11 == 10) x_checksum1 = 0;
		else x_checksum1 = x_checksum1%11;
    x_checksum2 = x_checksum2 + x_checksum1*mask2[10];
	if (x_checksum2%11 == 10) x_checksum2 = 0;
		else x_checksum2 = x_checksum2%11;
	sprintf(x_retval, "%s%d%d", x_retval, x_checksum1, x_checksum2);
	return x_retval;
}


// Get date of birth day
char* generate_dob() {

	char* result_year;


	int year  = 1975 + (rand()%16);

	result_year = (char*)malloc(4);
	memset(result_year,0,4);

	if (year == 1981) {
		year = year + 1;
	}

	itoa(year, result_year, 10);

	return result_year;
}


