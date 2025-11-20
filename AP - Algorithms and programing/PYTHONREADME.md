# PythonProjects
My college python projects

# Assigment 1:
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


# Assigment 2:
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


# Assigment 4:
A math teacher needs a program that helps students perform different vector 
operations.
Assignment 4 (A4) Solving complex problems with Python
Camelia Chira 2 Algorithms and Programming
1st. Iteration
A vector (class MyVector) is identified by the following properties:
• name_id given as a string/int
• colour given as one letter (possible values ‘r’, ‘g’, ‘b’, ‘y’ and ‘m’)
• type given as a positive integer greater or equal to 1
• values given as a list of numbers
The following features are offered by the program (to be implemented in class MyVector):
1. Scalar operations:
a. Add a scalar to a vector – add_scalar
    e.g. [1,2,3] + 2 = [3,4,5]

2. Vector operations:
a. Add two vectors –
    e.g. [1,2,3] + [4,5,6] = [5,7,9]
b. Subtract two vectors – subtract
    e.g. [1,2,3] - [4,5,5] = [-3,-3,-2]
c. Multiplication – multiplication
    e.g. [1,2,3] * [4,5,5] = 29

3. Reduction operations
a. Sum of elements in a vector
    e.g. for [1,2,3] sum is 6
b. Product of elements in a vector
    e.g. for [1,2,3] product is 6
c. Average of elements in a vector
    e.g. for [1,2,3] average is 2
d. Minimum of a vector
    e.g. for [1,-2,3] minimum is -2
e. Maximum of a vector
    e.g. for [1,2,-3] maximum is 2

2nd. Iteration
The program manages several vectors (class MyVectorRepository ) and allows 
operations such as:
1. Add a vector to the repository
2. Get all vectors
3. Get a vector at a given index
4. Update a vector at a given index
5. Update a vector identified by name_id
6. Delete a vector by index
7. Delete a vector by name_id
Assignment 4 (A4) Solving complex problems with Python
Camelia Chira 3 Algorithms and Programming
8. Plot all vectors in a chart based on the type and colour of each vector (using 
library matplotlib). Type should be interpreted as follows: 1 – circle, 2 – square, 
3 – triangle, any other value – diamond. (No tests needed for this function)
9. Get the sum of elements in all vectors.
10. Get the vector which represents the sum of all vectors.
11. Get the list of vectors having a given sum of elements.
12. Get the list of vectors having the minimum less than a given value.
13. Get the sum of all the elements in those vectors having a given color.
14. Get the max of all vectors having the sum greater than a given value. 
15. Get the min of all vectors.
16. Get a list of values representing the multiplication of consecutive vectors in the 
repository.
17. Delete all vectors from the repository. 18. Delete all vectors for which the color 
is a given value.
18. Delete all vectors for which the product of elements is greater than a given 
value.
19. Delete all vectors that are between two given indexes.
20. Delete all vectors for which the max value is equal to a given value.
21. Update all vectors by adding a given scalar to each element.
22. Update the color of a vector identified by name_id.
23. Update all vectors having a given type by setting their color to the same given 
value.

3rd. Iteration
Implement all features from iteration 1 using special libraries e.g. numpy

# Assigment 5:
Considering an airport, there are several planes (identified by name/number, airline 
company, number of seats, destination, list of passengers) and each plane has certain 
passengers (identified by first name, last name and passport number).
1. Develop an application to allow CRUD operations on Passenger and Plane .
2. The application should be layered, tested and validated.
3. Sort the passengers in a plane by last name
4. Sort planes according to the number of passengers
5. Sort planes according to the number of passengers with the first name starting 
with a given substring
6. Sort planes according to the string obtained by concatenation of the number of 
passengers in the plane and the destination
7. Identify planes that have passengers with passport numbers starting with the 
same 3 letters
8. Identify passengers from a given plane for which the first name or last name 
contain a string given as parameter
9. Identify plane/planes where there is a passenger with given name
10. Form groups of k passengers from the same plane but with different last names 
k is a value given by the user)
11. Form groups of k planes with the same destination but belonging to different 
airline companies (k is a value given by the user)
