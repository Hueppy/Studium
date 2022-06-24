package de.fhbielefeld.pmdungeon.controller;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import de.fhbielefeld.pmdungeon.behaviors.AnxiousBehaviorStrategy;
import de.fhbielefeld.pmdungeon.behaviors.BehaviorStrategy;
import de.fhbielefeld.pmdungeon.behaviors.MeleeBehaviorStrategy;
import de.fhbielefeld.pmdungeon.behaviors.RangedBehaviorStrategy;
import de.fhbielefeld.pmdungeon.behaviors.SwitchingBehaviorStrategy;
import de.fhbielefeld.pmdungeon.desktop.DesktopLauncher;
import de.fhbielefeld.pmdungeon.entities.Bag;
import de.fhbielefeld.pmdungeon.entities.Character;
import de.fhbielefeld.pmdungeon.entities.Chest;
import de.fhbielefeld.pmdungeon.entities.Collidable;
import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.entities.Item;
import de.fhbielefeld.pmdungeon.entities.MeleeWeapon;
import de.fhbielefeld.pmdungeon.entities.MimicChest;
import de.fhbielefeld.pmdungeon.entities.Monster;
import de.fhbielefeld.pmdungeon.entities.Ogre;
import de.fhbielefeld.pmdungeon.entities.Potion;
import de.fhbielefeld.pmdungeon.entities.QuestGiver;
import de.fhbielefeld.pmdungeon.entities.RangedWeapon;
import de.fhbielefeld.pmdungeon.entities.Weapon;
import de.fhbielefeld.pmdungeon.entities.traps.SpawnTrap;
import de.fhbielefeld.pmdungeon.entities.traps.Spikes;
import de.fhbielefeld.pmdungeon.entities.traps.Trap;
import de.fhbielefeld.pmdungeon.hud.ActiveQuestsScreen;
import de.fhbielefeld.pmdungeon.hud.HeartIcon;
import de.fhbielefeld.pmdungeon.hud.InventoryIcon;
import de.fhbielefeld.pmdungeon.hud.InventoryScreen;
import de.fhbielefeld.pmdungeon.hud.LevelProgressFragment;
import de.fhbielefeld.pmdungeon.hud.LevelText;
import de.fhbielefeld.pmdungeon.hud.QuestScreen;
import de.fhbielefeld.pmdungeon.inventory.Inventory;
import de.fhbielefeld.pmdungeon.quests.CollectingQuest;
import de.fhbielefeld.pmdungeon.quests.ProgressionQuest;
import de.fhbielefeld.pmdungeon.quests.Quest;
import de.fhbielefeld.pmdungeon.skills.Invisibility;
import de.fhbielefeld.pmdungeon.skills.Skill;
import de.fhbielefeld.pmdungeon.skills.Sprint;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.game.Controller.MainController;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.logging.ConsoleHandler;
import java.util.logging.FileHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;

/** Implementierung des MainControllers. */
public class Start extends MainController {
  private static final Logger logger = Logger.getLogger(Start.class.getName());
  private static final Random random = new Random();
  private Hero hero;
  private List<Monster> monster;
  private List<Item> items;
  private Chest chest;
  private List<Trap> traps;
  private InventoryScreen inventoryScreen;
  private QuestScreen questScreen;
  private CollisionController collisionController;
  private QuestGiver questGiver;
  private ActiveQuestsScreen activeQuestsScreen;
  private List<IEntity> newEntities;

  /** Haupteinstiegspunkt. */
  public static void main(String[] args) {
    try {
      LogManager.getLogManager().reset();

      Handler console = new ConsoleHandler();
      console.setLevel(Level.INFO);
      Handler file = new FileHandler("log.txt", true);
      file.setLevel(Level.FINEST);

      Logger root = Logger.getLogger("");
      root.addHandler(console);
      root.addHandler(file);

      logger.info("=== START ===");
      DesktopLauncher.run(new Start());
    } catch (Exception e) {
      logger.log(Level.SEVERE, "Exception in main", e);
    }
  }

  /** Initialisierung des Spiels. */
  @Override
  public void setup() {
    logger.entering(this.getClass().getName(), "setup");

    this.traps = new ArrayList<>();
    for (int i = 0; i < 5; i++) {
      Spikes spikes = new Spikes();
      this.traps.add(spikes);
      entityController.addEntity(spikes);
    }

    Inventory<Item> heroInventory = new Inventory<>(10);
    List<Skill> skills = new ArrayList<>();
    hero =
        new Hero(
            () -> {
              this.firstFrame = true;
            },
            heroInventory,
            skills,
            (i) -> {
              dropItem(i, hero.getPosition());
            });
    entityController.addEntity(hero);
    camera.follow(hero);

    skills.add(new Sprint(hero));
    skills.add(new Invisibility(hero));

    entityController.addEntity(new LevelText(textHUD, hero));

    for (int i = 0; i < 5; i++) {
      hud.addHudElement(new HeartIcon(i, hero));
    }

    hud.addHudElement(new LevelProgressFragment(hero, 0, LevelProgressFragment.Type.Start));
    for (int i = 1; i < 9; i++) {
      hud.addHudElement(new LevelProgressFragment(hero, i, LevelProgressFragment.Type.Middle));
    }
    hud.addHudElement(new LevelProgressFragment(hero, 9, LevelProgressFragment.Type.End));

    for (int i = 0; i < 10; i++) {
      hud.addHudElement(new InventoryIcon<>(heroInventory, i));
    }

    this.monster = new ArrayList<>();
    this.items = new ArrayList<>();

    chest = new Chest(new Inventory<>(10));
    entityController.addEntity(chest);

    this.inventoryScreen = new InventoryScreen();
    this.questScreen = new QuestScreen();
    this.activeQuestsScreen = new ActiveQuestsScreen();

    this.collisionController = new CollisionController();

    this.collisionController.registerCollidable(hero);
    this.collisionController.registerCollidables(monster);
    this.collisionController.registerCollidables(items);
    this.collisionController.registerCollidables(traps);
    this.collisionController.registerCollidable(chest);

    this.collisionController.registerHandler(
        Hero.class,
        Item.class,
        (x, y) -> {
          if (!y.isPickedUp() && x.pickup(y)) {
            y.setVisible(false);
            y.setPickedUp(true);
          }
        });

    this.collisionController.registerHandler(
        Hero.class,
        Chest.class,
        (x, y) -> {
          inventoryScreen.show(chest.getInventory());

          if (Gdx.input.isKeyJustPressed(Input.Keys.F)) {
            for (Item i : chest.empty()) {
              items.add(i);
              entityController.addEntity(i);
              i.setLevel(chest.getLevel());
              dropItem(i, chest.getPosition());
            }
          }
        });

    this.collisionController.registerHandler(
        Hero.class,
        QuestGiver.class,
        (x, y) -> {
          if (y.deleteable()) {
            return;
          }

          Quest quest = y.getQuest();
          questScreen.show(quest);

          if (Gdx.input.isKeyJustPressed(Input.Keys.F)) {
            x.accept(quest);
          }
        });

    this.collisionController.registerHandler(
        Hero.class,
        Monster.class,
        (x, y) -> {
          x.attack(y);
        });
    this.collisionController.registerHandler(
        Monster.class,
        Hero.class,
        (x, y) -> {
          x.attack(y);
        });

    this.collisionController.registerHandler(
        Hero.class,
        Trap.class,
        (x, y) -> {
          y.activate(x);
        });
    this.collisionController.registerHandler(
        Monster.class,
        Trap.class,
        (x, y) -> {
          y.activate(x);
        });

    this.collisionController.registerHandler(
        Hero.class,
        RangedWeapon.Projectile.class,
        (x, y) -> {
          Character owner = y.getOwner().getOwner();
          if (owner != x) {
            y.getOwner().getOwner().attack(x);
          }
        });
    this.collisionController.registerHandler(
        Monster.class,
        RangedWeapon.Projectile.class,
        (x, y) -> {
          Character owner = y.getOwner().getOwner();
          if (owner != x) {
            y.getOwner().getOwner().attack(x);
          }
        });

    this.newEntities = new ArrayList<>();

    logger.exiting(this.getClass().getName(), "setup");
  }

  private void addEntity(IEntity entity) {
    newEntities.add(entity);
  }

  private void dropItem(Item item, Point position) {
    final DungeonWorld dungeon = levelController.getDungeon();
    Point p;
    do {
      p = new Point(position);
      p.x += random.nextFloat() * 2f - 1f;
      p.y += random.nextFloat() * 2f - 1f;
    } while (!dungeon.isTileAccessible(p));
    item.setLevel(dungeon);
    item.setPosition(p);
    item.setVisible(true);
    item.setPickedUp(false);
  }

  /** Event Handler für den Beginn eines neuen Frames. */
  protected void beginFrame() {
    logger.entering(this.getClass().getName(), "beginFrame");

    logger.exiting(this.getClass().getName(), "beginFrame");
  }

  /** Event Handler für das Ende eines neuen Frames. */
  public void endFrame() {
    logger.entering(this.getClass().getName(), "endFrame");

    if (levelController.checkForTrigger(hero.getPosition())) {
      levelController.triggerNextStage();
    }

    activeQuestsScreen.show(hero.getQuests());

    collisionController.update();

    this.monster.removeIf((x) -> x.deleteable());
    this.items.removeIf((x) -> x.deleteable());

    for (IEntity e : newEntities) {
      entityController.addEntity(e);
      if (e instanceof Collidable) {
        collisionController.registerCollidable((Collidable) e);
      }
    }
    newEntities.clear();

    logger.exiting(this.getClass().getName(), "endFrame");
  }

  private void initializeBehavior(Monster monster) {
    BehaviorStrategy behavior;
    int r = random.nextInt(4);
    switch (r) {
      case 0:
        behavior = new RangedBehaviorStrategy(monster, hero);
        break;
      case 1:
        behavior = new MeleeBehaviorStrategy(monster, hero);
        break;
      case 2:
        behavior =
            new SwitchingBehaviorStrategy(
                monster,
                hero,
                new MeleeBehaviorStrategy(monster, hero),
                new RangedBehaviorStrategy(monster, hero));
        break;
      default:
        behavior = new AnxiousBehaviorStrategy(monster);
        break;
    }

    monster.setBehavior(behavior);
  }

  /** Event Handler, wenn ein neues Level geladen wird. */
  public void onLevelLoad() {
    logger.entering(this.getClass().getName(), "onLevelLoad");

    DungeonWorld level = levelController.getDungeon();
    hero.setDungeon(level);

    for (Trap t : this.traps) {
      if (t instanceof Spikes) {
        t.setDungeon(level);
      } else {
        entityController.removeEntity(t);
      }
    }
    this.traps.removeIf((x) -> !(x instanceof Spikes));
    for (int i = 0; i < 1; i++) {
      SpawnTrap spawnTrap =
          new SpawnTrap(
              hero,
              (m) -> {
                initializeBehavior(m);
                this.monster.add(m);
                entityController.addEntity(m);
                m.setDungeon(level);
              });
      this.traps.add(spawnTrap);
      entityController.addEntity(spawnTrap);
      spawnTrap.setDungeon(level);
    }

    for (Monster m : this.monster) {
      entityController.removeEntity(m);
    }
    this.monster.clear();
    for (int i = 0; i < 2; i++) {
      Monster m = new Ogre();
      this.monster.add(m);
      entityController.addEntity(m);
      m.setDungeon(level);
      Weapon w = new RangedWeapon(this::addEntity);
      entityController.addEntity(w);
      w.setLevel(level);
      w.use(m);

      initializeBehavior(m);
    }
    for (int i = 0; i < 3; i++) {
      Monster m = new MimicChest();
      this.monster.add(m);
      entityController.addEntity(m);
      m.setDungeon(level);

      initializeBehavior(m);
    }

    for (Item i : this.items) {
      entityController.removeEntity(i);
    }
    this.items.clear();
    for (int i = 0; i < 2; i++) {
      Potion p = new Potion();
      this.items.add(p);
      entityController.addEntity(p);
      p.setLevel(level);
    }
    for (int i = 0; i < 1; i++) {
      Weapon w = new RangedWeapon(this::addEntity);
      this.items.add(w);
      entityController.addEntity(w);
      w.setLevel(level);
    }
    for (int i = 0; i < 1; i++) {
      Bag<Weapon> b = new Bag(new Inventory(10));
      this.items.add(b);
      entityController.addEntity(b);
      b.setLevel(level);
    }

    if (questGiver != null) {
      entityController.removeEntity(questGiver);
    }
    Quest quest;
    if (random.nextFloat() > 0.5f) {
      quest = new CollectingQuest(30, List.of(), Potion.class, 2);
    } else {
      quest = new ProgressionQuest(40, List.of(new MeleeWeapon(MeleeWeapon.Type.Cleaver)));
    }

    questGiver = new QuestGiver(level, quest);
    this.collisionController.registerCollidable(questGiver);
    entityController.addEntity(questGiver);

    chest.setLevel(level);
    Inventory<Item> chestInventory = chest.getInventory();
    chestInventory.add(new MeleeWeapon(MeleeWeapon.Type.Cleaver));
    chestInventory.add(new Potion());
    chestInventory.add(new Potion());
    chestInventory.add(new Potion());

    logger.exiting(this.getClass().getName(), "onLevelLoad");
  }
}
