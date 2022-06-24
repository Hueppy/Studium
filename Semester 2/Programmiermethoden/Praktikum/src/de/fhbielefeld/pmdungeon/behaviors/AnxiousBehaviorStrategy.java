package de.fhbielefeld.pmdungeon.behaviors;

import de.fhbielefeld.pmdungeon.entities.Monster;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.dungeonconverter.Coordinate;

/** "Ängstliche" Verhaltenstrategie. */
public class AnxiousBehaviorStrategy extends PathFindingBehaviorStrategy {
  public AnxiousBehaviorStrategy(Monster monster) {
    super(monster);
  }

  @Override
  protected Coordinate getTargetLocation() {
    return monster.getDungeon().getRandomLocationInDungeon();
  }
}
