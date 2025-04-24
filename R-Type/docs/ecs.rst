===================
ECS Documentation
===================

ECS Overview
------------

The Entity Component System (ECS) is a design pattern commonly used in game development. ECS is preferred for its performance, modularity, and scalability.

- **Entities**: Represent game objects or actors (e.g., player, enemies, background). An entity is identified uniquely.
- **Components**: Contain data (no behavior) that define an entity's properties, such as position, velocity, or drawable state.
- **Systems**: Logic and behavior that operate on entities with specific components.

Class Purpose and Interactions
------------------------------

SparseArray (Generic Container for Components)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    template <typename Component>
    class SparseArray { /* ... */ };

**Usage**:
The `SparseArray` is instantiated per component type and managed by the Registry.

**Purpose**:
- Acts as a data storage for components of a specific type.
- Manages components using ``std::vector<std::optional<Component>>`` to allow fast access with sparse indexing.

**Provides**:
- **Insert**: Add or replace a component at a specific index.
- **Emplace**: Construct a component in place.
- **Erase**: Remove a component at a given index.
- **Iterators**: For traversing components.

**Key Methods**:
- ``insert_at(SizeType pos, Component const& comp)``: Add a component at a specific position.
- ``emplace_at(SizeType pos, Params&&... args)``: Construct a component at a position.
- ``erase(SizeType pos)``: Remove a component.
- ``operator[](size_t idx)``: Access components directly.

---

Registry
^^^^^^^^

.. code-block:: cpp

    class Registry { /* ... */ };

**Purpose**:
- Central class for managing entities and components.
- Provides registration and access to components of specific types.
- Owns an `EntitiesManagement` class to handle entity lifecycle.

**Key Responsibilities**:
1. **Component Management**:
   - ``register_component<Component>()``: Registers a new component type.
   - ``get_components<Component>()``: Accesses all components of a given type.
   - ``remove_component``: Removes a specific component from an entity.

2. **Entity Management**:
   - Entity creation, deletion, and component association are delegated to the nested `EntitiesManagement` class.

3. **Erase Functionality**:
   - Maintains erase functions (``_erase_functions``) to remove components dynamically.

**Relationships**:
- `EntitiesManagement` manages individual entities and their components using the `SparseArray` storage.
- `SparseArray` is used internally for each component type.

---

EntitiesManagement
^^^^^^^^^^^^^^^^^^

.. code-block:: cpp

    class EntitiesManagement { /* ... */ };

**Purpose**:
- Handles entity lifecycle: creation (``spawn_entity``), deletion (``kill_entity``), and component attachment.
- Provides APIs for adding and removing components.

**Key Methods**:
- ``spawn_entity()``: Creates a new entity and assigns a unique ID.
- ``add_component<Component>()``: Attaches a component to an entity.
- ``emplace_component<Component>()``: Constructs and attaches a component.

**Example Interaction**:

.. code-block:: cpp

    entity_t square = registry._entitiesManager.spawn_entity();
    registry._entitiesManager.add_component<position>(square, position{150, 200});
    registry._entitiesManager.add_component<velocity>(square, velocity{0.5, 0});

---

Entity
^^^^^^

.. code-block:: cpp

    class Entity { /* ... */ };

**Purpose**:
- Represents a unique identifier for each game object.
- Provides implicit conversion to ``size_t`` for indexing into `SparseArray`.

**Components**:
Components are plain data structures representing properties of entities.

**Example Components**:

.. code-block:: cpp

    struct position { float x, y; };
    struct velocity { float vx, vy; };
    struct drawable { sf::Sprite sprite; int status; };
    struct scale { float sx, sy; };
    struct controllable { int status; };

- **position**: Stores (x, y) coordinates.
- **velocity**: Tracks movement speed.
- **drawable**: Contains rendering information.
- **scale**: Defines scaling properties.
- **controllable**: Marks entities that can be controlled by input.

---

Systems
-------

Systems operate on entities that have specific components. Each system performs logic related to its components.

**`position_system`**:

- **Purpose**: Updates the position of entities based on their velocity.
- **Operates on**: `position` and `velocity`.

.. code-block:: cpp

    void position_system(Registry &r) {
        auto &positions = r.get_components<position>();
        auto const &velocities = r.get_components<velocity>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); i++) {
            if (positions[i] && velocities[i]) {
                positions[i]->x += velocities[i]->vx;
                positions[i]->y += velocities[i]->vy;
            }
        }
    }

**`control_system`**:

- **Purpose**: Handles player input and modifies velocity or other properties.
- **Operates on**: `controllable` and `velocity`.

.. code-block:: cpp

    void control_system(Registry &r) {
        auto &controllables = r.get_components<controllable>();
        auto &velocities = r.get_components<velocity>();

        for (size_t i = 0; i < controllables.size() && i < velocities.size(); i++) {
            if (controllables[i] && velocities[i]) {
                // Modify velocity based on input (placeholder logic)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) velocities[i]->vx -= 0.5;
            }
        }
    }

**`draw_system`**:

- **Purpose**: Renders drawable entities on the screen.
- **Operates on**: `position` and `drawable`.

.. code-block:: cpp

    void draw_system(Registry &r, sf::RenderWindow &window) {
        auto const &positions = r.get_components<position>();
        auto const &drawables = r.get_components<drawable>();

        for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
            if (positions[i] && drawables[i]) {
                drawables[i]->sprite.setPosition(positions[i]->x, positions[i]->y);
                window.draw(drawables[i]->sprite);
            }
        }
    }

---

Workflow of the ECS
-------------------

1. **Initialization**:
   - Components are registered using ``register_component<T>()``.
   - Entities are created and components are attached to them.

2. **Game Loop**:
   - Systems operate on registered entities:
     - `control_system`: Captures user input.
     - `position_system`: Updates positions based on velocities.
     - `draw_system`: Renders entities to the window.

3. **Registry Structure**:
   - Registry manages all components using `SparseArray`.
   - Systems access components directly via the registry for efficient iteration.

---

Benefits of ECS
---------------

1. **Performance**:
   - Data-oriented design allows cache-friendly iterations.
2. **Scalability**:
   - New components and systems can be added without modifying existing code.
3. **Modularity**:
   - Systems are decoupled from each other and operate independently.

---

Key Takeaways
-------------

- **Registry**: Central hub managing components and entities.
- **SparseArray**: Efficient data storage for components.
- **Systems**: Encapsulate logic for entities with specific components.
- **Entities**: Serve as IDs linking components together.
