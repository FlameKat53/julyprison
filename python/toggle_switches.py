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
        self.geometry("400x380")
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

        # Four toggle switches with different colors
        switches = [
            ("Switch 1",   "#7aa2f7"),
            ("Switch 2",   "#9ece6a"),
            ("Switch 3", "#f7768e"),
            ("Switch 4",  "#e0af68"),
        ]

        for name, on_color in switches:
            self._make_switch(name, on_color)

    def _make_switch(self, name, on_color):
        frame = tk.Frame(self, bg="#1e1e2e")
        frame.pack(pady=10)

        # Label
        tk.Label(
            frame, text=name, font=("Arial", 13, "bold"),
            bg="#1e1e2e", fg="#c0caf5"
        ).pack(side=tk.LEFT, padx=(0, 15))

        # Canvas-based toggle
        var = tk.BooleanVar(value=False)
        sw_w, sw_h = 64, 32
        canvas = tk.Canvas(
            frame, width=sw_w, height=sw_h,
            highlightthickness=0, cursor="hand2", bg="#1e1e2e"
        )
        canvas.pack(side=tk.LEFT)

        def draw(state):
            canvas.delete("all")
            color = on_color if state else "#45475a"
            r = sw_h // 2  # radius for rounding

            # Left semi-circle
            canvas.create_arc(0, 0, r * 2, r * 2,
                              start=90, extent=180,
                              style=tk.CHORD, fill=color, outline="")
            # Right semi-circle
            canvas.create_arc(sw_w - r * 2, 0, sw_w, r * 2,
                              start=270, extent=180,
                              style=tk.CHORD, fill=color, outline="")
            # Middle rectangle
            canvas.create_rectangle(r, 0, sw_w - r, sw_h,
                                    fill=color, outline="")

            # Knob
            knob = sw_h - 10
            knob_x = sw_w - sw_h + 4 if state else 4
            canvas.create_oval(knob_x, 3, knob_x + knob, 3 + knob,
                               fill="white", outline="#cccccc", width=1)

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
