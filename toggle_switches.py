#!/usr/bin/env python3
"""
A simple GUI application with four toggle switches.
Works on CachyOS (Arch Linux) with Python 3 + tkinter.
"""

import tkinter as tk


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Toggle Switches")
        self.geometry("400x350")
        self.resizable(False, False)
        self.configure(bg="#1e1e2e")

        # Title
        tk.Label(
            self, text="Toggle Switches",
            font=("Arial", 18, "bold"),
            bg="#1e1e2e", fg="#cdd6f4"
        ).pack(pady=(30, 5))

        tk.Label(
            self, text="These switches do absolutely nothing",
            font=("Arial", 10),
            bg="#1e1e2e", fg="#a6adc8"
        ).pack(pady=(0, 25))

        # Four toggle switches
        for i in range(1, 5):
            self._make_switch(f"Switch {i}")

    def _make_switch(self, name):
        frame = tk.Frame(self, bg="#1e1e2e")
        frame.pack(pady=10)

        # Label
        tk.Label(
            frame, text=name, font=("Arial", 13, "bold"),
            bg="#1e1e2e", fg="#cdd6f4"
        ).pack(side=tk.LEFT, padx=(0, 15))

        # Canvas-based toggle
        var = tk.BooleanVar(value=False)
        canvas = tk.Canvas(
            frame, width=60, height=30,
            highlightthickness=0, cursor="hand2"
        )
        canvas.pack(side=tk.LEFT)

        def draw(state):
            canvas.delete("all")
            color = "#4CAF50" if state else "#555555"
            canvas.create_rectangle(0, 0, 60, 30, fill=color, outline="", width=0)
            knob_x = 40 if state else 4
            canvas.create_oval(knob_x, 3, knob_x + 24, 27, fill="white", outline="", width=0)

        draw(False)

        def toggle(event=None):
            var.set(not var.get())
            draw(var.get())

        canvas.bind("<Button-1>", toggle)


def main():
    app = App()
    app.mainloop()


if __name__ == "__main__":
    main()
