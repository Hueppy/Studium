package de.fhbielefeld.pmdungeon.behaviors;

import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.entities.Monster;
import de.fhbielefeld.pmdungeon.entities.Weapon;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.dungeonconverter.Coordinate;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.Calendar;
import java.util.GregorianCalendar;

/** Verhaltensstrategie für den Fernkampf. */
public class RangedBehaviorStrategy extends PathFindingBehaviorStrategy {
  private static final int DISTANCE = 4;
  private final Hero hero;
  private GregorianCalendar nextWeaponUse;

  public RangedBehaviorStrategy(Monster monster, Hero hero) {
    super(monster);
    this.hero = hero;
  }

  @Override
  protected Coordinate getTargetLocation() {
    Point monsterPosition = monster.getPosition();
    if (!hero.isVisible()) {
      return new Coordinate((int) monsterPosition.x, (int) monsterPosition.y);
    }

    Point heroPosition = hero.getPosition();

    double x = monsterPosition.x - heroPosition.x;
    double y = monsterPosition.y - heroPosition.y;

    double angle = Math.atan(x / y);

    DungeonWorld level = monster.getDungeon();
    for (int i = DISTANCE; i > 0; i--) {
      int targetX = (int) (heroPosition.x + Math.sin(angle) * i);
      int targetY = (int) (heroPosition.y + Math.cos(angle) * i);

      if (level.isTileAccessible(targetX, targetY)) {
        return new Coordinate(targetX, targetY);
      }
    }
    return new Coordinate((int) monsterPosition.x, (int) monsterPosition.y);
  }

  @Override
  public void update() {
    super.update();

    Weapon weapon = monster.getWeapon();

    GregorianCalendar now = new GregorianCalendar();
    if (hero.isVisible() && weapon != null && !now.before(this.nextWeaponUse)) {
      Point monsterPosition = monster.getPosition();
      Point heroPosition = hero.getPosition();
      Point velocity = monster.getVelocity();

      double x = heroPosition.x - monsterPosition.x;
      double y = heroPosition.y - monsterPosition.y;

      double angle = Math.atan2(x, y);
      Point direction =
          new Point(
              (float) Math.sin(angle) * 0.2f + velocity.x,
              (float) Math.cos(angle) * 0.2f + velocity.y);

      weapon.attack(direction);

      now.add(Calendar.MILLISECOND, 500);
      this.nextWeaponUse = now;
    }
  }
}
