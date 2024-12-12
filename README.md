# C program for solving a minimization problem using Hooke-Jeeves method
## Algorithm:
While the desired accuracy isn't reached:
   1. Exploratory search from basic point
   2. If the search was successful:
      1. Pattern search (moving along the vector until the improvement stops)
      2. Remembering the new basic point
   3. Else:

      Step reduction
