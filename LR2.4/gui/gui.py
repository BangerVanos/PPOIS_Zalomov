import tkinter as tk
from tkinter import messagebox
import regex as re
from atm_interface.atm_interface import AtmInterface
from atm.atm import ATM
from plastic_card.plastic_card import PlasticCard
from typing import Optional
from money_vault.money_vault import MoneyVault
import exceptions.exceptions as exc


class GuiAtm(AtmInterface):
    pin_attempts: int = 3
    root = tk.Tk()
    root.geometry('640x480')
    root.title('ATM')
    frame = tk.Frame(root)

    @classmethod
    def clear_window(cls):
        for widget in cls.frame.winfo_children():
            widget.destroy()
        cls.frame.pack_forget()

    @classmethod
    def start(cls):
        cls.clear_window()
        enter_label = tk.Label(cls.frame, text='Enter card number', font=('Arial', 20))
        enter_label.pack()
        card_number = tk.StringVar(cls.root)
        card_number_field = tk.Entry(cls.frame, textvariable=card_number, font=('Arial', 20))
        card_number_field.pack()
        submit_button = tk.Button(cls.frame, text='Enter', font=('Arial', 20),
                                  command=lambda: cls.__make_card(card_number.get()))
        submit_button.pack(pady=5)
        cls.frame.place(relx=0.5, rely=0.5, anchor='center')

    @classmethod
    def __make_card(cls, card_num: str):
        if not bool(re.fullmatch(r'\d{16}', card_num)):
            messagebox.showinfo('Error', 'Wrong card number!')
            return
        plastic_card: Optional[PlasticCard] = cls.find_card_by_card_num(card_num)
        if plastic_card is None:
            messagebox.showinfo('Error', 'ATM is closed on maintenance\n(enter existing card)')
            cls.root.quit()
            return

    @classmethod
    def run(cls):
        cls.start()
        cls.root.mainloop()
