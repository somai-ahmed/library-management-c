# Library Management System in C

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Windows-informational?style=flat-square)
![Status](https://img.shields.io/badge/status-completed-success?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-green?style=flat-square)

A full-featured library management system built in C — covering catalog management, loan tracking, and statistics through a clean console interface.

---

## Introduction

This project presents the development of a library management application in C, designed to automate book and loan management, facilitate return and overdue tracking, and provide useful statistics.

The system relies on **parallel arrays** to store book information and a **2D integer matrix** to record loan records — implementing complete features such as catalog management, constrained borrow/return operations, and activity statistics generation.

---

## Features

### Part 1 — Book Management
- Display all books in the catalog
- Add new books with duplicate number validation
- Remove existing books
- Update the number of available copies
- Search books by number or title (partial match supported)
- Display only available books (with at least 1 copy)

### Part 2 — Loan Management
- Register new loans (with constraint enforcement)
- View all active loans
- View loans by member (via 8-digit CIN)
- Display loans sorted by expected return date
- Record book returns and update stock automatically
- Detect and display overdue books
- Delete loan records by time period

### Part 3 — Statistics
- Total count of books, members, and loans
- Most borrowed books overall
- Books never borrowed
- Most borrowed books within a custom time period
- Most frequent borrowers

---

## Data Structures

### Books — Parallel Arrays

```c
int numeros[MAX_LIVRES];               // Unique book numbers
char titres[MAX_LIVRES][MAX_TITRE];    // Book titles (max 100 chars)
int nbexemplaires[MAX_LIVRES];         // Number of available copies
int nbLivres;                          // Total book count
```

### Loans — 2D Integer Matrix

```c
int matriceEmprunts[MAX_EMPRUNTS][8]
```

| Column | Content |
|---|---|
| `[0]` | Member CIN |
| `[1]` | Book number |
| `[2]` | Borrow day |
| `[3]` | Borrow month |
| `[4]` | Borrow year |
| `[5]` | Expected return day |
| `[6]` | Expected return month |
| `[7]` | Expected return year |

---

## Architecture

```
Main Menu
├── Book Management      (6 functions)
├── Loan Management      (7 functions)
└── Statistics           (5 functions)
```

---

## Technical Constraints

| Constraint | Value |
|---|---|
| Max books | 100 |
| Max loan records | 500 |
| Max title length | 100 characters |
| Max simultaneous loans per member | 7 |
| Max loan duration | 1 month |
| Member CIN format | Exactly 8 digits |

---

## Validation Mechanisms

| Area | Mechanism |
|---|---|
| Date validation | Format check (DD/MM/YYYY), day/month coherence, leap year handling, borrow < return date |
| CIN validation | Exactly 8 digits (10000000–99999999) |
| Book number | Uniqueness guaranteed on insertion |
| Loan period | Maximum 1 month enforced |
| Loan limit | Maximum 7 active loans per member |

---

## Key Technical Challenges

**Date comparison** — solved by converting dates to a comparable integer format `YYYYMMDD` for reliable ordering and range filtering.

**Heterogeneous loan data** — solved by using an 8-column integer matrix to unify CIN, book number, and both dates in a single structure.

**Loan limit enforcement** — real-time count of active loans per member CIN before any new registration.

**Array deletion** — classic element-shift loop with counter decrement and index adjustment (`i--`) to correctly handle multiple consecutive deletions.

**Period statistics** — double-bound date comparison (borrow date ≥ start AND borrow date ≤ end) after YYYYMMDD conversion.

---

## Getting Started

### Prerequisites

Make sure you have the following installed before cloning the project:

| Tool | Version | Download |
|---|---|---|
| GCC (MinGW on Windows) | 6.0+ | [mingw-w64.org](https://www.mingw-w64.org/) |
| Git | any | [git-scm.com](https://git-scm.com/) |
| Make (optional) | any | included with MinGW |

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/somai-ahmed/library-management-c.git
cd library-management-c
```

**2. Compile**

On Windows (MinGW / Code::Blocks):
```bash
gcc -Wall -std=c11 -o library main.c
```

On Linux / macOS:
```bash
make
```

> **Note:** This project uses `windows.h` (`Sleep`, `system("cls")`). On Linux/macOS, replace `Sleep(ms)` with `usleep(ms * 1000)` and `system("cls")` with `system("clear")` for cross-platform support.

**3. Run**

```bash
# Windows
library.exe

# Linux / macOS
./library
```

### Quick Start

Once running, you will be greeted with the main menu. Use the number keys to navigate:

```
1 → Book Management
2 → Loan Management
3 → Statistics
4 → Quit
```

The system comes preloaded with **12 sample books** and **8 demo loans** so you can explore all features immediately without entering data manually.

---

## Project Structure

```
library-management-c/
├── main.c       # Full source code
├── Makefile     # Build configuration
└── README.md
```

---

> [!NOTE]
> This application is currently available only in French. All interfaces, messages, and content are provided in French.

## Conclusion

This library management system in C is a complete and functional solution covering all essential library operations across three modules. The program meets all initial objectives:

- Full catalog management (add, remove, update, search)
- Rigorous loan tracking with automatic overdue detection
- Relevant statistics and activity analysis
- Robust data validation (dates, CIN, business rules)
- Structured hierarchical menu interface
