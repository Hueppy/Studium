package de.fhbielefeld.pmdungeon.test.quests;

import de.fhbielefeld.pmdungeon.entities.Item;
import de.fhbielefeld.pmdungeon.entities.MeleeWeapon;
import de.fhbielefeld.pmdungeon.entities.Potion;
import de.fhbielefeld.pmdungeon.inventory.Inventory;
import de.fhbielefeld.pmdungeon.quests.CollectingQuest;
import de.fhbielefeld.pmdungeon.quests.Quest;
import de.fhbielefeld.pmdungeon.quests.QuestTaker;
import java.util.List;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

/** Test für eine Sammelquest. */
public class CollectingQuestTest {
  private Inventory<Item> inventory;
  private QuestTakerMock taker;

  @Before
  public void setUp() throws Exception {
    this.inventory = new Inventory<Item>(10);
    this.taker = new QuestTakerMock();
  }

  @Test
  public void testCollectItemExpectQuestFinished() {
    CollectingQuest quest = new CollectingQuest(10, List.of(), Potion.class, 1);
    quest.setTaker(this.taker);

    inventory.register(quest);
    inventory.add(new Potion());

    Assert.assertTrue(this.taker.finished);

    inventory.unregister(quest);
  }

  @Test
  public void testCollectItemExpectQuestNotFinished() {
    CollectingQuest quest = new CollectingQuest(10, List.of(), Potion.class, 2);
    quest.setTaker(this.taker);

    inventory.register(quest);
    inventory.add(new Potion());

    Assert.assertFalse(this.taker.finished);

    inventory.unregister(quest);
  }

  @Test
  public void testRecollectItemExpectQuestNotFinished() {
    CollectingQuest quest = new CollectingQuest(10, List.of(), Potion.class, 2);
    quest.setTaker(this.taker);

    Item item1 = new Potion();

    inventory.register(quest);
    inventory.add(item1);
    inventory.remove(0);
    inventory.add(item1);

    Assert.assertFalse(this.taker.finished);

    inventory.unregister(quest);
  }

  @Test
  public void testWrongItemExpectQuestNotFinished() {
    CollectingQuest quest = new CollectingQuest(10, List.of(), Potion.class, 1);
    quest.setTaker(this.taker);

    Item item1 = new MeleeWeapon(MeleeWeapon.Type.Cleaver);

    inventory.register(quest);
    inventory.add(item1);

    Assert.assertFalse(this.taker.finished);

    inventory.unregister(quest);
  }

  private class QuestTakerMock implements QuestTaker {
    public boolean finished = false;

    @Override
    public void finished(Quest quest) {
      this.finished = true;
    }
  }
}
