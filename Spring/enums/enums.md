# Motivating example

Consider the following character struct:

```
typedef struct {
    const char *name;
    int level;
    int hp;
    int equipment_ids[4];
} character;
```

Maybe we want to reuse the same struct for players, NPCs, and enemies. How could we differentiate when we use these structs? We could make flags `bool is_player` etc. Or we could create an `int type` for the struct.

Enums make the second approach simpler and more direct.

# Enums

Here's the better way to implement the above. Enums let us create new constants aliased under a new type.

```
typedef enum {
    character_type_player,
    character_type_npc,
    character_type_enemy,
} character_type;

typedef struct {
    const char *name;
    int level;
    int hp;
    int equipment_ids[4];

    character_type type;
} character;

character player = {
    "Arongil",
    10,
    100,
    {0},
    character_type_player
};
```

It's possible to name the enum types more simply `player, npc, enemy`. However, it is best practice to prefix enum types so we don't clog up the global types.

Sometimes we want to set specific `int` values for the enumerators. For example, `character_type_enemy = 3` in the `enum` declaration. Although we might hope that the type of these variables would be `character_type`, the compiler is all cool with us writing nonsense like `character_type_player * 8`. You probably have no reason to do such voodoo.

And that's a wrap on enums!
