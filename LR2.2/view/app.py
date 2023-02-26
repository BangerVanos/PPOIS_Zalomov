from kivy.app import App
from kivy.uix.label import Label


class StudentsApp(App):
    def build(self):
        return Label(text="Hello world")
