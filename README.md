# DIVOC — Patient Management & Tracking System in C

> **Historical Archive Note:** This repository contains the original source code developed during the first semester of the 2020–2021 academic year. It is preserved exactly as submitted on the original deadline, without subsequent modifications, serving as a historical archive to document my technical progress and foundational programming work.

A command-line application written in **standard C** for managing, filtering, and tracking patients affected by an infectious disease (*Divoc*). Developed as the final project for the **Programming I** course in the Bachelor's Degree in Telecommunication Technologies Engineering at the **University of Vigo** (School of Telecommunication Engineering).

---

## Technical Design & Features

The project was designed adhering strictly to **structured and modular programming** principles, completely avoiding global variables and `goto` statements.

* **In-Memory Management & File Persistence:** Handles up to 256 patient records in memory using a dedicated `struct patient` data structure. On startup, it automatically loads existing records from `patients.txt` (if present) and serializes the updated database back to disk upon confirmed exit.
* **Robust Input/Output Validation:** Comprehensive keyboard input sanitization using safe buffer reading (`fgets` and `sscanf`), enforcing numeric range constraints, character limits, and allowed character sets against invalid user inputs.
* **Algorithmic ID (DNI) Verification:** Validates standard Spanish national ID format (8 digits followed by 1 uppercase letter) and calculates the expected control letter via modulo 23 arithmetic against the official string `"TRWAGMYFPDXBNJZSQVHLCKE"`.

---

## Program Features

The interactive menu provides 6 main operations via command characters (case-insensitive):

1. **`R` — Register a patient (`p_register`):** Interactively prompts for patient name (1–24 non-whitespace characters), valid DNI (9 characters), birth year (1900–2020), fever status (`y/n`), cough status (`y/n`), and additional symptoms (`F`: fatigue, `S`: loss of smell, `T`: loss of taste, `M`: muscle aches, `N`: none).
2. **`S` — Search for a patient (`p_search`):** Looks up a patient by DNI and displays their formatted record (`>NAME;DNI;YEAR;FEVER;COUGH;SYMPTOM;`).
3. **`D` — Discharge a patient (`p_discharge`):** Searches for a patient by DNI, removes their record, and shifts subsequent elements to keep the array contiguous.
4. **`L` — List patients by age (`p_list`):** Prompts for a cutoff birth year (1900–2020) and lists all patients born in or prior to that year.
5. **`P` — Identify positives (`p_mark`):** Filters and displays patients meeting positive infection criteria (concurrently presenting fever `1`, cough `1`, and an additional symptom other than `'N'`).
6. **`X` — Exit the program (`p_exit`):** Asks for user confirmation and saves all active patient records to `patients.txt`, preserving memory order.

---

## Project Structure

```text
.
├── src/
│   ├── database.c    # Business logic and patient database operations
│   ├── database.h    # struct patient definition and database prototypes
│   ├── divoc.c       # Main module: application entry point and CLI menu
│   ├── inout.c       # I/O handling, input parsing, and validation routines
│   ├── inout.h       # I/O module header
│   └── Makefile      # Original GCC build script
├── .gitignore
└── README.md
```

---

## Build & Execution

### Prerequisites
* GCC-compatible C compiler (`gcc`).
* GNU `make` utility.

### Instructions

1. Clone the repository and navigate to the source directory (`src/`):
   ```bash
   git clone https://github.com/alvaro-maquieira/divoc.git
   cd divoc/src
   ```

2. Build the project using the original `Makefile` (compiled with `-Wall`):
   ```bash
   make
   ```

3. Run the executable:
   ```bash
   ./divoc
   ```

4. Clean up compiled binaries and intermediate object files (`*.o`, `divoc`):
   ```bash
   make clean
   ```

---

## Interface Preview

```text
--------------------------------------------------
|                     DIVOC_                     |
--------------------------------------------------

R) Register a patient
S) Search for a patient
D) Discharge a patient
L) List patients by age
P) Mark positive

X) Exit the program

Choose an option (RSDLPX): 
```