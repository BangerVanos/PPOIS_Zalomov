import pygame
import scripts.configs as cf
from typing import Any, Union


class MovementDirection:
    RIGHT = (False, False)
    LEFT = (True, False)


class Enemy(pygame.sprite.Sprite):
    def __init__(self, group, spawn_x: Union[int, float], spawn_y: Union[int, float], animation_frames_path: list[str],
                 rel_size: tuple, movement_speed: int, movement_direction: MovementDirection, map_size: cf.MapSize):
        super(Enemy, self).__init__()
        self.add(group)
        self.display = pygame.display.get_surface()
        self.frames = []
        for frame in animation_frames_path:
            image = pygame.image.load(frame)
            image = pygame.transform.smoothscale(image, (int(self.display.get_width() * rel_size[0] / 100),
                                                         int(self.display.get_width() * rel_size[1] / 100)))
            image = pygame.transform.flip(image, movement_direction[0], movement_direction[1])
            self.frames.append(image)
        self.index = 0
        self.image = self.frames[self.index % len(self.frames)]
        self.rect = self.image.get_rect()
        self.rect.center = (spawn_x, spawn_y)
        self.counter = 0
        self.map_size = map_size
        self.movement_speed = -1 * movement_speed if movement_direction == MovementDirection.LEFT else movement_speed
        self.movement_speed = round(movement_speed / self.display.get_width(), 2)

    def update(self, *args: Any, **kwargs: Any) -> None:
        animation_speed = 4

        # movement
        self.rect.centerx += self.movement_speed

        # update animation
        self.counter += 1
        if self.counter >= animation_speed:
            self.counter = 0
            self.index += 1
            self.image = self.frames[self.index % len(self.frames)]

        if self.rect.centerx > self.map_size[0] + self.rect.w or self.rect.centerx < -self.rect.w:
            self.kill()
