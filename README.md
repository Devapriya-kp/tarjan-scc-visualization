# Tarjan's Algorithm - SCC Simulation (GTK4)

## 📌 Description
This project demonstrates the working of **Tarjan's Algorithm** to find **Strongly Connected Components (SCCs)** in a directed graph.

The graph is visualized using **GTK4**, where:
- Nodes represent entities (users)
- Edges represent connections
- Each SCC is displayed using a different color

---

## ⚙️ How It Works

1. User enters:
   - Number of nodes
   - Number of edges
   - Directed edges

2. The program:
   - Runs Tarjan's Algorithm
   - Identifies SCCs

3. Output:
   - Console: Displays SCC group of each node
   - GUI: Displays graph with colored components

---

## 🧪 Sample Input
Enter number of nodes: 8
Enter number of edges: 12
Enter edges:
0 1
1 2
2 0
2 3
3 4
4 5
5 3
6 5
6 7
7 6
1 6
4 7


---

## 📤 Sample Output (Console)
Node 0 -> SCC 0
Node 1 -> SCC 0
Node 2 -> SCC 0
Node 3 -> SCC 1
Node 4 -> SCC 1
Node 5 -> SCC 1
Node 6 -> SCC 2
Node 7 -> SCC 2


---

## 🖥️ GUI Output

- Nodes are displayed as circles
- Edges represent connections
- Different colors represent different SCCs

<img width="688" height="492" alt="Screenshot 2026-05-20 084618" src="https://github.com/user-attachments/assets/0906df79-9f98-47a6-861a-a5522f242d7b" />

<img width="596" height="424" alt="Screenshot 2026-05-20 084606" src="https://github.com/user-attachments/assets/24910ef3-f0bd-4981-9247-97d125b66a23" />



---

## 🛠️ Technologies Used

- C Programming
- GTK4 (for visualization)
- Tarjan’s Algorithm (DFS based)

---

## ▶️ How to Run

```bash
gcc main.c `pkg-config --cflags --libs gtk4` -o tarjan
./tarjan
