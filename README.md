# PythonProjects
My college python projects

Assigment 1:
1.1) Compute the control digit of an integer by summing up its digits, then summing up the digits of the sum, so on, until a sum of only one digit is obtained.
    e.g. The control digit of integer number 1971 is 9 (1971 → 18 → 9).

1.5) Determine the value of the element at index k in the array 1, 2, 2, 3, 3, 3, 4, 4, 4, 4,… without reading or effectively creating the array.
    e.g. Input: k = 35, Output: 8

1.9) Print all numbers with maximum 2 digits of form xy with the property that the last digit of (xy)^2 is y.
    e.g. 5^2=25 or 10^2=100 or 76^2=5776.

1.13) Read a natural number n. Form another number from its digits found at odd positions (from left to right).
    e.g. Input: 1234, Output: 13

1.17) A number n is special if there is a natural number m such that n = m + S(m), where S(m) is the sum of digits of m. Verify if a given number is special.
    e.g. 1235 is special (1235=1225+10)


Assigment 2:
A math teacher needs a program to help students test different number properties. The program manages an array of numbers and allows students to use the following features offered by the program:
1. Add numbers in the array
1.1) add(my_list, value) - value as last element of my_list
1.2) insert(my_list, index, value) - insert number value at index (the index of the first element is 0)
   
2. Modify elements in the array
2.1) remove(my_list, index) - removes the element at index
2.2) remove(my_list, from_index, to_index) - removes elements between the two given index
   e.g.remove(my_list, 1,3)-removes the elements at indices 1, 2 and 3
2.3) replace(my_list, old_value, new_value) - replaces all old_values occurances with new_value
   e.g.replace(my_list, [1,3,5], [5,3])-replaces all sub-arrays 135 with 5 3

3. Get the numbers that have certain properties
3.1) prime(my_list, from index, to_index) - get prime number between the two given index
   e.g. prime(my_list, 1,5)-get the prime numbers from the array found at indices 1..5
3.2) odd(my_list, from index, to_index) - get odd number between the two given index
   e.g. odd(my_list, 1,5) - get the odd numbers from the array found at indices 1..5
   
4. Obtain different characteristics from sub-arrays
4.1) sum(my_list, from_index, to_index) - get sum of elements between the two given index
   e.g. sum(my_list, 1,5)-get the sum of elements 1..5
4.2) gcd (my_list, from_index, to_index) - get greatest common divisor of elements between the two given index
   e.g. gcd (my_list, 1, 5)-get the greatest common divisor of elements 1..5
4.3) max(my_list, from index, to_index) - get maximum of elements between the two given index
   e.g. max(my list, 1,5)-get the maximum of elements 1..5

5. Filter values
5.1) filter prime(my_list) - keep only prime numbers, remove the other elements
5.2) filter_negative (my_list) - keep only negative numbers, remove the other elements

6. Undo
6.1) undo() - undo the last operation that modified the array
