package de.fhbielefeld.pmdungeon.behaviors;

import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.entities.Monster;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.dungeonconverter.Coordinate;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Verhaltensstrategie für den Nahkampf. */
public class MeleeBehaviorStrategy extends PathFindingBehaviorStrategy {
  private final Hero hero;

  /** Erstellt eine neue Nahkampf-Verhaltensstrategie. */
  public MeleeBehaviorStrategy(Monster monster, Hero hero) {
    super(monster);
    this.hero = hero;
  }

  @Override
  protected Coordinate getTargetLocation() {
    if (!hero.isVisible()) {
      Point monsterPosition = monster.getPosition();
      return new Coordinate((int) monsterPosition.x, (int) monsterPosition.y);
    }

    Point position = hero.getPosition();
    return new Coordinate((int) (position.x + 0.5f), (int) (position.y + 0.5f));
  }
}
