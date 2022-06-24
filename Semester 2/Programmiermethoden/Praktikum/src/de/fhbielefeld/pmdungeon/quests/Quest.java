package de.fhbielefeld.pmdungeon.quests;

import de.fhbielefeld.pmdungeon.entities.Item;
import java.util.List;
import java.util.logging.Logger;

/** Abstrakte Basisklasse für eine Quest. */
public abstract class Quest {
  private static final Logger logger = Logger.getLogger(Quest.class.getName());
  private final int xp;
  private final List<Item> items;
  private QuestTaker taker;

  public Quest(int xp, List<Item> items) {
    this.xp = xp;
    this.items = items;
  }

  protected void finish() {
    logger.info("Quest finished");
    this.taker.finished(this);
  }

  public int getXp() {
    return xp;
  }

  public List<Item> getItems() {
    return items;
  }

  public QuestTaker getTaker() {
    return taker;
  }

  public void setTaker(QuestTaker taker) {
    logger.info(String.format("Set QuestTaker to [%s]", taker));
    this.taker = taker;
  }

  public abstract String getDescription();

  public boolean isAssigned() {
    return this.taker != null;
  }
}
