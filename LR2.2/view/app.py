from kivy.app import App
from kivy.lang.builder import Builder


class StudentsApp(App):
    def build(self):
        return Builder.load_file("view/students.kv")
