# 🧩 Guard Logic Challenge (C++)

This project implements a **decision-making system** for a secured facility with three doors, each leading to a different outcome:

- 🟢 **Green Door** → Safe Exit  
- 🔴 **Red Door** → Trap  
- 🟡 **Yellow Door** → Return to Start  

---

## 🚀 Features

- ⚡ **Priority-based decision system** for clear and deterministic outcomes  
- 🚨 **Alarm as highest priority (fail-safe override)**  
- 🪪 **Access control using keycard validation**  
- 🔁 **Continuous retry mechanism** for "back to start" scenarios  
- 🧱 **Clean and modular C++ design** using classes and structs  
- ⏱️ **System reset simulation** using delay (`std::this_thread::sleep_for`)  

---

## 🧠 Decision Logic (Priority Order)

The system evaluates conditions in the following order:

1. 🚨 **Alarm Triggered** → System resets, user must restart  
2. 🪪 **No Keycard** → Access denied, retry required  
3. 🔴 **Security Code = 3** → Trap (immediate termination)  
4. 🟢 **Security Code = 7 + Keycard** → Safe Exit  
5. 🟡 **Other Cases** → Return to Start (retry loop)  

---

## 🏗️ Design Approach

- 🧩 **Separation of concerns**
  - `GuardSystem` → decision logic  
  - `SystemState` → input state  
  - `Door` → outcome representation  

- 🎯 **Deterministic behavior**
  - No randomness → every output is explainable  

- 🔒 **Fail-safe mechanism**
  - Alarm overrides all actions to ensure safety  

- 🔁 **State-based looping**
  - System continues until a terminal state (Safe Exit / Trap)  

---

## ▶️ How to Run

```bash
g++ -std=c++17 Guard_Logic_Challenge.cpp -o guard
./guard
