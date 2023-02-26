from db.db import DbConnect
from db_interaction import StudentInteractor


class StudentModel:
    def __init__(self):
        self.interactor = StudentInteractor(DbConnect())
        self.students = list()

    def all(self):
        return self.interactor.all()

    def get(self, filtered_options: dict):
        return self.interactor.get(filtered_options)

    def delete(self, delete_options: dict):
        deleted_notes_count = self.interactor.delete(delete_options)
        return deleted_notes_count
