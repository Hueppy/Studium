package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.inventory.Inventory;
import de.fhbielefeld.pmdungeon.observers.InventoryObserver;
import de.fhbielefeld.pmdungeon.observers.ProgressionObserver;
import de.fhbielefeld.pmdungeon.quests.Quest;
import de.fhbielefeld.pmdungeon.quests.QuestTaker;
import de.fhbielefeld.pmdungeon.skills.Skill;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.graphic.Animation;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Constants;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Consumer;
import java.util.logging.Logger;

/** Implementierung des Helden. */
public class Hero extends Character implements QuestTaker {
  private static final Logger logger = Logger.getLogger(Hero.class.getName());
  private static final int DEFAULT_HEALTH = 420;
  private static final int DEFAULT_ATTACK = 69; /* nice */
  private static final Animation idle =
      new Animation(
          Arrays.asList(
              new Texture("assets/frames/big_zombie_idle_anim_f0.png"),
              new Texture("assets/frames/big_zombie_idle_anim_f1.png"),
              new Texture("assets/frames/big_zombie_idle_anim_f2.png"),
              new Texture("assets/frames/big_zombie_idle_anim_f3.png")),
          4);
  private static final Animation walk =
      new Animation(
          Arrays.asList(
              new Texture("assets/frames/big_zombie_run_anim_f0.png"),
              new Texture("assets/frames/big_zombie_run_anim_f1.png"),
              new Texture("assets/frames/big_zombie_run_anim_f2.png"),
              new Texture("assets/frames/big_zombie_run_anim_f3.png")),
          4);
  private static final Animation invisible_idle =
      new Animation(
          Arrays.asList(
              new Texture("assets/frames/big_zombie_idle_invis_anim_f0.png"),
              new Texture("assets/frames/big_zombie_idle_invis_anim_f1.png"),
              new Texture("assets/frames/big_zombie_idle_invis_anim_f2.png"),
              new Texture("assets/frames/big_zombie_idle_invis_anim_f3.png")),
          4);
  private static final Animation invisible_walk =
      new Animation(
          Arrays.asList(
              new Texture("assets/frames/big_zombie_run_invis_anim_f0.png"),
              new Texture("assets/frames/big_zombie_run_invis_anim_f1.png"),
              new Texture("assets/frames/big_zombie_run_invis_anim_f2.png"),
              new Texture("assets/frames/big_zombie_run_invis_anim_f3.png")),
          4);
  private final Runnable onDeath;
  private final Inventory<Item> inventory;
  private final List<Skill> skills;
  private final Consumer<Item> onDrop;
  private final List<ProgressionObserver> observers;
  private final List<Quest> quests;
  private int experience;
  private int level = 1;
  private boolean visible = true;
  private boolean sprinting;

  /** Erstellt einen Helden. */
  public Hero(
      Runnable onDeath, Inventory<Item> inventory, List<Skill> skills, Consumer<Item> onDrop) {
    super(DEFAULT_HEALTH, DEFAULT_ATTACK);
    logger.entering(getClass().getName(), "ctor");
    logger.info("Creating Hero");
    this.onDeath = onDeath;
    this.inventory = inventory;
    this.skills = skills;
    this.onDrop = onDrop;
    this.quests = new ArrayList<>();
    this.observers = new ArrayList<>();

    logger.exiting(getClass().getName(), "ctor");
  }

  @Override
  protected Animation getIdleAnimation() {
    if (visible) {
      return idle;
    } else {
      return invisible_idle;
    }
  }

  @Override
  protected Animation getWalkAnimation() {
    if (visible) {
      return walk;
    } else {
      return invisible_walk;
    }
  }

  @Override
  protected Point calculateVelocity() {
    logger.entering(getClass().getName(), "calculateVelocity");
    Point velocity = new Point(0.0f, 0.0f);

    final float movementSpeed = sprinting ? 0.15f : 0.1f;

    if (Gdx.input.isKeyPressed(Input.Keys.D)) {
      logger.fine("Key 'D' pressed");
      velocity.x = movementSpeed;
    }
    if (Gdx.input.isKeyPressed(Input.Keys.A)) {
      logger.fine("Key 'A' pressed");
      velocity.x = -movementSpeed;
    }
    if (Gdx.input.isKeyPressed(Input.Keys.W)) {
      logger.fine("Key 'W' pressed");
      velocity.y = movementSpeed;
    }
    if (Gdx.input.isKeyPressed(Input.Keys.S)) {
      logger.fine("Key 'S' pressed");
      velocity.y = -movementSpeed;
    }

    logger.exiting(getClass().getName(), "calculateVelocity");
    return velocity;
  }

  @Override
  public void update() {
    super.update();

    if (Gdx.input.isKeyJustPressed(Input.Keys.I)) {
      this.inventory.show();
    }
    Item item = null;
    if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_0)) {
      item = this.inventory.remove(0);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_1)) {
      item = this.inventory.remove(1);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_2)) {
      item = this.inventory.remove(2);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_3)) {
      item = this.inventory.remove(3);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_4)) {
      item = this.inventory.remove(4);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_5)) {
      item = this.inventory.remove(5);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_6)) {
      item = this.inventory.remove(6);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_7)) {
      item = this.inventory.remove(7);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_8)) {
      item = this.inventory.remove(8);
    } else if (Gdx.input.isKeyJustPressed(Input.Keys.NUM_9)) {
      item = this.inventory.remove(9);
    }
    if (item != null) {
      if (Gdx.input.isKeyPressed(Input.Keys.CONTROL_LEFT)) {
        this.onDrop.accept(item);
      } else {
        item.use(this);
      }
    }
    if (this.weapon != null && Gdx.input.isButtonJustPressed(Input.Buttons.LEFT)) {
      int x = Gdx.input.getX() - Constants.WIDTH / 2;
      int y = Gdx.input.getY() - Constants.HEIGHT / 2;

      double angle = Math.atan2(x, y);
      Point direction =
          new Point(
              (float) Math.sin(angle) * 0.2f + this.velocity.x,
              -(float) Math.cos(angle) * 0.2f + this.velocity.y);

      this.weapon.attack(direction);
    }

    skills.stream().filter((x) -> x.unlockedAt() <= level).forEach((x) -> x.update());
  }

  @Override
  protected void successfulAttack(Character other) {
    super.successfulAttack(other);
    this.restore(this.attack / 10);
    this.experience(other.getAttack() / 2);
  }

  @Override
  public void damage(Character from, int damage) {
    logger.entering(getClass().getName(), "damage");
    super.damage(from, damage);

    logger.info(String.format("took %d damage, new health: %d", damage, this.health));

    if (from != null) {
      Point position = this.getPosition();
      Point fromPosition = from.getPosition();
      Point newPosition = new Point(0f, 0f);
      float length = 0.75f;
      do {
        newPosition.x = position.x + Math.copySign(length, position.x - fromPosition.x);
        newPosition.y = position.y + Math.copySign(length, position.y - fromPosition.y);
        length /= 2;
      } while (!this.getDungeon().isTileAccessible(newPosition));
      this.position = newPosition;
    }

    if (this.health <= 0) {
      logger.info("GAME OVER");
      this.health = DEFAULT_HEALTH;
      this.onDeath.run();
    }
    logger.exiting(getClass().getName(), "damage");
  }

  @Override
  public void setAttack(int attack) {
    super.setAttack((int) (attack * Math.pow(1.05, level)));
  }

  /**
   * Aufheben eines Gegenstands.
   *
   * @param i der aufzuhebende Gegenstand
   * @return false, wenn das Inventar voll ist, sonst true
   */
  public boolean pickup(Item i) {
    logger.info(String.format("Picking up %s", i));
    boolean result = this.inventory.add(i);
    logger.info(result ? "Item was saved in inventory" : "Item could not be stored");
    return result;
  }

  @Override
  public void equip(Weapon weapon) {
    if (this.weapon != null) {
      weapon.setVisible(false);
      this.inventory.add(weapon);
    }
    super.equip(weapon);
  }

  /**
   * Hinzufügen von Erfahrungspunkten.
   *
   * @param experience Erfahrungspunkte
   */
  public void experience(int experience) {
    this.experience += experience;
    if (this.experience > 100) {
      this.experience -= 100;
      this.level++;
      updateAttack();
    }
  }

  private void notify(DungeonWorld level) {
    ArrayList<ProgressionObserver> observers = new ArrayList<>(this.observers);
    for (ProgressionObserver observer : observers) {
      observer.update(level);
    }
  }

  /** Registriert einen ProgressionObserver am Helden. */
  public void register(ProgressionObserver observer) {
    this.observers.add(observer);
  }

  /** Unregistriert einen ProgressionObserver am Helden. */
  public void unregister(ProgressionObserver observer) {
    this.observers.remove(observer);
  }

  public int getExperience() {
    return experience;
  }

  public int getLevel() {
    return level;
  }

  public boolean isVisible() {
    return visible;
  }

  public void setVisible(boolean visible) {
    this.visible = visible;
  }

  public boolean isSprinting() {
    return sprinting;
  }

  public void setSprinting(boolean sprinting) {
    this.sprinting = sprinting;
  }

  @Override
  public void setDungeon(DungeonWorld dungeon) {
    super.setDungeon(dungeon);
    notify(dungeon);
  }

  @Override
  public void finished(Quest quest) {
    experience(quest.getXp());
    for (Item item : quest.getItems()) {
      if (!this.inventory.add(item)) {
        this.onDrop.accept(item);
      }
    }

    if (quest instanceof InventoryObserver) {
      inventory.unregister((InventoryObserver) quest);
    }
    if (quest instanceof ProgressionObserver) {
      unregister((ProgressionObserver) quest);
    }

    this.quests.remove(quest);
  }

  /** Nimmt die übergebene Quest an. */
  public void accept(Quest quest) {
    this.quests.add(quest);
    quest.setTaker(this);

    if (quest instanceof InventoryObserver) {
      inventory.register((InventoryObserver) quest);
    }
    if (quest instanceof ProgressionObserver) {
      register((ProgressionObserver) quest);
    }
  }

  public List<Quest> getQuests() {
    return quests;
  }
}
