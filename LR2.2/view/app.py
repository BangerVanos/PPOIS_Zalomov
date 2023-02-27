from kivymd.app import MDApp
from kivymd.uix.dialog import MDDialog
from kivy.lang.builder import Builder
from kivymd.uix.boxlayout import MDBoxLayout
from kivymd.uix.gridlayout import MDGridLayout
from kivymd.uix.button import MDRectangleFlatButton


class AddDialogWidget(MDGridLayout):
    pass


class StudentsAppMainWidget(MDBoxLayout):
    def __init__(self, **kwargs):
        super(StudentsAppMainWidget, self).__init__(**kwargs)
        self.dialog = None

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
        print('-'*10)
        print(f"Фамилия: {self.dialog.content_cls.ids.last_name.text}")
        print(f"Имя: {self.dialog.content_cls.ids.first_name.text}")
        print(f"Отчество: {self.dialog.content_cls.ids.middle_name.text}")
        print(f"Номер группы: {self.dialog.content_cls.ids.group_number.text}")
        illness_hours = int(self.dialog.content_cls.ids.illness_hours.text)
        other_hours = int(self.dialog.content_cls.ids.other_hours.text)
        bad_hours = int(self.dialog.content_cls.ids.bad_hours.text)
        all_hours = illness_hours + other_hours + bad_hours
        print(f"Пропуски по болезни: {illness_hours}")
        print(f"Пропуски по другим причинам: {other_hours}")
        print(f"Пропуски н/у: {bad_hours}")
        print(f"Всех пропусков: {all_hours}")

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

    def close_dialog(self, obj):
        self.dialog.dismiss()


class StudentsApp(MDApp):
    def build(self):
        self.theme_cls.primary_palette = "Indigo"
        return Builder.load_file("view/students.kv")
