from kivymd.app import MDApp
from kivymd.uix.dialog import MDDialog
from kivy.lang.builder import Builder
from kivymd.uix.gridlayout import MDGridLayout
from kivymd.uix.button import MDRectangleFlatButton
from controller.controller import Controller
from kivymd.uix.screen import MDScreen
from kivymd.uix.screenmanager import MDScreenManager


class StudentsAppMainScreen(MDScreen):
    pass


class AddStudentScreen(MDScreen):
    def __init__(self, **kwargs):
        super(AddStudentScreen, self).__init__(**kwargs)
        self.controller = Controller()
        self.dialog = None

    def send_add_data(self):
        student_info = dict()
        student_info['last_name'] = self.ids.last_name.text
        if student_info['last_name'] in ('', None):
            self.validation_dialog("Фамилия - обязательный параметр")
            return
        student_info['first_name'] = self.ids.first_name.text
        if student_info['first_name'] in ('', None):
            self.validation_dialog("Фамилия - обязательный параметр")
            return
        student_info['middle_name'] = self.ids.middle_name.text
        student_info['group_number'] = self.ids.group_number.text
        student_info['illness_hours'] = self.ids.illness_hours.text
        student_info['illness_hours'] \
            = 0 if student_info['illness_hours'] in ('', None) else abs(int(student_info['illness_hours']))
        student_info['other_hours'] = self.ids.other_hours.text
        student_info['other_hours'] \
            = 0 if student_info['other_hours'] in ('', None) else abs(int(student_info['other_hours']))
        student_info['bad_hours'] = self.ids.bad_hours.text
        student_info['bad_hours'] \
            = 0 if student_info['bad_hours'] in ('', None) else abs(int(student_info['bad_hours']))
        self.controller.add(student_info)

    def validation_dialog(self, text: str):
        self.dialog = MDDialog(
            title=text,
            buttons=[MDRectangleFlatButton(
                text="Понятно",
                on_release=self.close_dialog
            )
            ]
        )
        self.dialog.open()

    def close_dialog(self, obj):
        self.dialog.dismiss()


class StudentsScreenManager(MDScreenManager):
    pass


class StudentsApp(MDApp):

    def build(self):
        self.theme_cls.primary_palette = "Indigo"
        Builder.load_file("view/kv/students.kv")
        Builder.load_file("view/kv/add_student_screen.kv")
        Builder.load_file("view/kv/all_student_screen.kv")
        screen_manager = StudentsScreenManager()
        screen_manager.add_widget(StudentsAppMainScreen(name='main'))
        screen_manager.add_widget(AddStudentScreen(name='add_student'))
        return screen_manager
