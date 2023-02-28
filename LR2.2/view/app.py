from kivymd.app import MDApp
from kivymd.uix.dialog import MDDialog
from kivy.lang.builder import Builder
from kivymd.uix.boxlayout import MDBoxLayout
from kivymd.uix.gridlayout import MDGridLayout
from kivymd.uix.button import MDRectangleFlatButton
from controller.controller import Controller


class AddDialogWidget(MDGridLayout):
    pass


class StudentsAppMainWidget(MDBoxLayout):
    def __init__(self, **kwargs):
        super(StudentsAppMainWidget, self).__init__(**kwargs)
        self.dialog = None
        self.controller = Controller()

    def show_add_dialog(self):
        dialog_widget = Builder.load_file("view/add_dialog.kv")
        self.dialog = MDDialog(
            title="Добавить нового студента",
            buttons=[MDRectangleFlatButton(text="Добавить", on_release=self.send_add_data),
                     MDRectangleFlatButton(text="Отмена", on_release=self.close_dialog)],
            size_hint=(.9, None),
            content_cls=dialog_widget
        )
        self.dialog.add_widget(dialog_widget)
        self.dialog.open()

    def send_add_data(self, obj):
        student_info = dict()
        student_info['last_name'] = self.dialog.content_cls.ids.last_name.text
        if student_info['last_name'] is None:
            self.validation_dialog("Фамилия - обязательный параметр")
            return
        student_info['first_name'] = self.dialog.content_cls.ids.first_name.text
        if student_info['first_name'] is None:
            self.validation_dialog("Фамилия - обязательный параметр")
            return
        student_info['middle_name'] = self.dialog.content_cls.ids.middle_name.text
        student_info['group_number'] = self.dialog.content_cls.ids.group_number.text
        student_info['illness_hours'] = self.dialog.content_cls.ids.illness_hours.text
        student_info['illness_hours'] \
            = 0 if student_info['illness_hours'] is None else abs(int(student_info['illness_hours']))
        student_info['other_hours'] = self.dialog.content_cls.ids.other_hours.text
        student_info['other_hours'] \
            = 0 if student_info['other_hours'] is None else abs(int(student_info['other_hours']))
        student_info['bad_hours'] = self.dialog.content_cls.ids.bad_hours.text
        student_info['bad_hours'] \
            = 0 if student_info['bad_hours'] is None else abs(int(student_info['bad_hours']))
        self.controller.add(student_info)

    def show_find_dialog(self):
        close_button = MDRectangleFlatButton(text="Отмена", on_release=self.close_dialog)
        find_button = MDRectangleFlatButton(text="Найти")
        grid_layout = MDGridLayout(
            rows=2,
            cols=7
        )
        self.dialog = MDDialog(
            title="Найти студентов по параметрам",
            buttons=[find_button, close_button]
        )
        self.dialog.add_widget(grid_layout)
        self.dialog.open()

    def validation_dialog(self, text: str):
        self.dialog = MDDialog(
            title=text,
            buttons=MDRectangleFlatButton(
                text="Понятно",
                on_release=self.close_dialog
            )
        )

    def close_dialog(self, obj):
        self.dialog.dismiss()


class StudentsApp(MDApp):
    def build(self):
        self.theme_cls.primary_palette = "Indigo"
        return Builder.load_file("view/students.kv")
