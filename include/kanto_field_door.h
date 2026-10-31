#ifndef GUARD_KANTO_FIELD_DOOR_H
#define GUARD_KANTO_FIELD_DOOR_H

// Portes de Kanto : code de Rouge Feu (src/kanto_field_door.c, généré par tools/kanto/gen_door.py).
void Kanto_FieldSetDoorOpened(int x, int y);
void Kanto_FieldSetDoorClosed(int x, int y);
s8 Kanto_FieldAnimateDoorClose(int x, int y);
s8 Kanto_FieldAnimateDoorOpen(int x, int y);
bool8 Kanto_FieldIsDoorAnimationRunning(void);
u16 Kanto_GetDoorSoundEffect(int x, int y);

#endif // GUARD_KANTO_FIELD_DOOR_H
