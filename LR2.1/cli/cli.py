from atm.atm import ATM
from typing import Optional
import exceptions.exceptions as exc


class AtmInterface:
    def __init__(self) -> None:
        self.__atm: Optional[ATM] = None

    def start(self):
        pass
