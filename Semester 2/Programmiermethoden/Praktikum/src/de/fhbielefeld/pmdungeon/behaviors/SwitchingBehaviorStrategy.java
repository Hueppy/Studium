package de.fhbielefeld.pmdungeon.behaviors;

import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.entities.Monster;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Verhaltsstrategie die abhängig zur Nahe des Helden die Strategie wechselt. */
public class SwitchingBehaviorStrategy extends BehaviorStrategy {
  private final int distance = 2;
  private final Hero hero;
  private final BehaviorStrategy near;
  private final BehaviorStrategy far;

  /** Erstellt eine neue Wechselstrategie. */
  public SwitchingBehaviorStrategy(
      Monster monster, Hero hero, BehaviorStrategy near, BehaviorStrategy far) {
    super(monster);
    this.hero = hero;
    this.near = near;
    this.far = far;
  }

  @Override
  public void update() {
    Point monsterPosition = monster.getPosition();
    Point heroPosition = hero.getPosition();

    double x = heroPosition.x - monsterPosition.x;
    double y = heroPosition.y - monsterPosition.y;

    double distance = Math.sqrt(x * x + y * y);

    if (distance < this.distance) {
      near.update();
    } else {
      far.update();
    }
  }
}
