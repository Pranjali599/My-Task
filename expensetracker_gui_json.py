import tkinter as tk
from tkinter import messagebox, ttk
import json
import os
from datetime import datetime
# ================= FILE ================= #
FILE_NAME = "expenses.json"
def load_data():
    if os.path.exists(FILE_NAME):
        with open(FILE_NAME, "r") as f:
            return json.load(f)
    return []
def save_data():
    with open(FILE_NAME, "w") as f:
        json.dump(expenses, f, indent=4)
# ================= DATA ================= #
expenses = load_data()
# ================= WINDOW ================= #
root = tk.Tk()
root.title("Expense Tracker - JSON Version")
root.geometry("750x800")
root.config(bg="#1e1e2f")
# ================= FUNCTIONS ================= #
def show_expenses():
    listbox.delete(0, tk.END)
    if not expenses:
        listbox.insert(tk.END, "No expenses found!")
        return
    for i, exp in enumerate(expenses, start=1):
        listbox.insert(
            tk.END,
            f"{i}. {exp['name']} | ₹{exp['amount']} | {exp['category']} | {exp['date']}"
        )
def add_expense():
    name = entry_name.get()
    amount = entry_amount.get()
    category = combo_category.get()
    date = entry_date.get()
    if name == "" or amount == "":
        messagebox.showwarning("Input Error", "Please fill all details")
        return
    try:
        amount = float(amount)
    except:
        messagebox.showerror("Error", "Amount must be number")
        return
    if date.strip() == "":
        date = datetime.now().strftime("%Y-%m-%d")
    expense = {
        "name": name,
        "amount": amount,
        "category": category,
        "date": date
    }
    expenses.append(expense)
    save_data()
    entry_name.delete(0, tk.END)
    entry_amount.delete(0, tk.END)
    entry_date.delete(0, tk.END)
    update_total()
    show_expenses()
def delete_expense():
    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("Select", "Please select expense")
        return
    index = selected[0]
    if index < len(expenses):
        expenses.pop(index)
    save_data()
    update_total()
    show_expenses()
def update_total():
    total = sum(float(exp["amount"]) for exp in expenses)
    label_total.config(text=f"Total Expense: ₹ {total}")
# ================= TITLE ================= #
title = tk.Label(
    root,
    text="💰 EXPENSE TRACKER (JSON)",
    font=("Arial", 24, "bold"),
    bg="#1e1e2f",
    fg="#00ffcc"
)
title.pack(pady=20)
# ================= FORM ================= #
card = tk.Frame(root, bg="#2a2a40", padx=20, pady=20)
card.pack(pady=10)
tk.Label(card, text="Name", bg="#2a2a40", fg="white").grid(row=0, column=0, sticky="w")
entry_name = tk.Entry(card, width=30)
entry_name.grid(row=0, column=1, pady=5)
tk.Label(card, text="Amount", bg="#2a2a40", fg="white").grid(row=1, column=0, sticky="w")
entry_amount = tk.Entry(card, width=30)
entry_amount.grid(row=1, column=1, pady=5)
tk.Label(card, text="Category", bg="#2a2a40", fg="white").grid(row=2, column=0, sticky="w")
combo_category = ttk.Combobox(card, values=["Food", "Travel", "Shopping", "Bills", "Other"])
combo_category.grid(row=2, column=1)
combo_category.set("Food")
tk.Label(card, text="Date", bg="#2a2a40", fg="white").grid(row=3, column=0, sticky="w")
entry_date = tk.Entry(card, width=30)
entry_date.grid(row=3, column=1, pady=5)
# ================= BUTTONS ================= #
btn_frame = tk.Frame(root, bg="#1e1e2f")
btn_frame.pack(pady=10)
tk.Button(btn_frame, text="Add Expense", command=add_expense,
          bg="#00c896", fg="white", width=15).grid(row=0, column=0, padx=5)
tk.Button(btn_frame, text="Show Expenses", command=show_expenses,
          bg="#2196F3", fg="white", width=15).grid(row=0, column=1, padx=5)
tk.Button(btn_frame, text="Delete", command=delete_expense,
          bg="#ff4d4d", fg="white", width=15).grid(row=0, column=2, padx=5)
# ================= LISTBOX ================= #
listbox = tk.Listbox(
    root,
    width=85,
    height=18,
    font=("Consolas", 11),
    bg="#111827",
    fg="white",
    selectbackground="#00ffcc"
)
listbox.pack(pady=20)
# ================= TOTAL ================= #
label_total = tk.Label(
    root,
    text="Total Expense: ₹ 0",
    font=("Arial", 18, "bold"),
    bg="#1e1e2f",
    fg="#00ffcc"
)
label_total.pack(pady=10)
# ================= LOAD DATA ================= #
update_total()
show_expenses()
root.mainloop() 