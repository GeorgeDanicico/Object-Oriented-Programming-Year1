#define _CRT_SECURE_NO_WARNINGS
#define NMAX 100005
#include <stdio.h>

int insert_command()
{// This function will return the command that the users entered.
	int command;
	printf("Enter the command: ");
	scanf("%d", &command);
	return command;
}

int return_array(int *array_Numbers)
{
	int length, i;
	printf("Enter the length: ");
	scanf("%d", &length);

	// Read the elements of the array
	for (i = 0; i < length; ++i)
		scanf("%d", array_Numbers + i);

	return length;
}

int check_if_prime(int number)
{
	// This function checks if a number is prime or not.
	int i;
	if (number < 2)
		return 0;
	if (number == 2)
		return 1;
	if (number % 2 == 0)
		return 0;

	for (i = 3; i * i <= number; i += 2)
		if (number % i == 0)
			return 0;
	return 1;
}

void eratostene_sieve(int given_number)
{
	// This function will generate all the prime numbers smaller than a given number 
	// In case there is no smaller prime number, a message will be displayed on the screen.
	int erato[NMAX], i, j, atleast_one_prime = 0;

	memset(erato, 0, 100005);
	erato[0] = erato[1] = 1;
	if (given_number >= 2)
		for (i = 2; i <= 1000; i++)
		{
			if (erato[i] == 0)
			{
				atleast_one_prime = 1;
				for (j = i * i; j < NMAX; j += i)
					erato[j] = 1;
			}
		}

	if (atleast_one_prime == 0)
		printf("There are no smaller prime number than %d \n", given_number);
	else {
		printf("The smaller prime numbers are: ");
		for (i = 2; i <= given_number; i++)
			if (erato[i] == 0)
				printf("%d ", i);
		printf("\n");
	}

}

void generate_prime_numbers()
{
	int given_number = 0;
	printf("Read a number: ");
	scanf("%d", &given_number);

	eratostene_sieve(given_number);

}

void find_longest_sequence(int length, int *array_Numbers)
{
	// This is the function that finds the longest sequence where each 2 consecutive elements have their sum equal to a prime number.
	int i, max_length_seq = 1, current_seq_length = 1, max_end = 1;

	for (i = 0; i < length; i++)
	{
		// We can compute the longest sequence when we read the elements.
		// We begin checking only when the second element has been read.
		if (i >= 1)
		{
			// If the sum of the 2 consecutive elements is a prime number
			// It means that they form/are in valid sequence.
			// If their sum is not a prime number, we check if the length of the current valid sequence is greater than the maximum length
			// And if true, we update the data.
			int sum = *(array_Numbers + i) + *(array_Numbers + i - 1);
			if (check_if_prime(sum))
				current_seq_length += 1;
			else
			{
				if (current_seq_length >= max_length_seq)
					max_length_seq = current_seq_length, max_end = i - 1;
				current_seq_length = 1;
			}
			if (current_seq_length >= max_length_seq)
				max_length_seq = current_seq_length, max_end = i;
		}
	}
	// Printing the longest sequence...
	printf("The longest sequence is: ");
	for (i = max_end - max_length_seq + 1; i <= max_end; i++)
		printf("%d ", *(array_Numbers + i));

}

void print_menu()
{
	// This is the function that contains the menu.
	printf("Menu: \n");
	printf("1. Enter an array of elements.\n");
	printf("2. Generate all the primes number smaller than a given number.\n");
	printf("3. Longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number.(Step 1 mandatory before!)\n");
	printf("0. Exit the application.\n");
}

int main()
{
	// If array_inserted = 0 it means that an array of numbers was not inserted, otherwise it will be 1.
	int done = 1, command, array_Numbers[1005], length = 0, array_inserted = 0;

	while (done)
	{
		print_menu();
		command = insert_command();
		if (!command)
			done = 0;
		else if (command == 1)
			length = return_array(array_Numbers), array_inserted = 1;
		else if (command == 2)
			generate_prime_numbers();
		else if (command == 3)
			if (!array_inserted)
				printf("You must enter firstly an array!.\n");
			else
				find_longest_sequence(length, array_Numbers);
		else printf("Invalid command.");

		printf("\n");

	}
	return 0;
}