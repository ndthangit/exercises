
# Graph Search on a Large Graph

## Dataset
The dataset [sgb-words](http://www-cs-faculty.stanford.edu/~knuth/sgb-words.txt) 
## Question
The dataset consists mostly of English words with a length of 5 characters. From this data, we construct a graph G = (V, E), where the vertex set V includes every word in sgb-words. There is an edge between two words u and v in G if u and v differ at exactly one position.

In graph G, the sequence of words: `words, wolds, golds, goads, grads, grade, grape, graph` forms a path, starting from the vertex "words" and ending at the vertex "graph."

## Tasks

### (a) Count Connected Components
Write a program to count the number of connected components in graph G.

### (b) Shortest Path
Write a program that takes input for the starting word \(u\) and ending word \(v\). Display the shortest path from \(u\) to \(v\) on the screen.

# How to Use

1. **Clone the repository:**

    ```bash
    git clone https://github.com/ndthangit/exercises_on_class.git
    ```

2. **Compile and run the programs:**

   - **Task (a): Count Connected Components**
   
     ```bash
     g++ exerciseA.cpp -o count_connected_components
     ./count_connected_components
     ```

   - **Task (b): Shortest Path**
   
     ```bash
     g++ exerciseB.cpp -o shortest_path
     ./shortest_path
     ```
