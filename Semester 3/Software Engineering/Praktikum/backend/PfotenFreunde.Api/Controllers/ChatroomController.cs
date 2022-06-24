using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class ChatroomController : ControllerBase
{
	private PfotenFreundeContext context;

	public ChatroomController(PfotenFreundeContext context)
	{
		this.context = context;
	}
	
    /// <summary>
    /// Gets all chatrooms
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    [HttpGet]
    public IEnumerable<Chatroom> GetAll()
    {
		return this.context.Chatrooms;
    }
	
    /// <summary>
    /// Get information of the specified chatroom
    /// </summary>
    /// <param name="id">Id of the chatroom</param>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">Chatroom not found</response>
    [HttpGet("{id}")]
    public async Task<ActionResult<Chatroom>> Get(int id)
    {
		var chatroom = await this.context.Chatrooms.FindAsync(id);

		if (chatroom == null)
		{
			return NotFound();
		}

		return chatroom;
    }

    /// <summary>
    /// Creates a new Chatroom
    /// </summary>
    [HttpPost]
    public async Task<int> Post(Chatroom chatroom)
    {
        chatroom.StartedAt = DateTime.Now;
		var entry = await this.context.Chatrooms.AddAsync(chatroom);

		await this.context.SaveChangesAsync();
		
		return entry.Entity.Id;
    }

    /// <summary>
    /// Updates information of a chatroom
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    [HttpPatch("{id}")]
    public async Task Patch(int id, Chatroom chatroom)
    {
		chatroom.Id = id;
		this.context.Chatrooms.Update(chatroom);

		await this.context.SaveChangesAsync();
    }

    /// <summary>
    /// Gets all users of the chatroom
    /// </summary>
    /// <response code="404">Chatroom not found</response>
    [HttpGet("{id}/user")]
    public async Task<ActionResult<IEnumerable<User>>> GetUsers(int id)
    {
		var chatroom = await this.context.Chatrooms
            .Include(x => x.Users)
            .FirstAsync(x => x.Id == id);
        
        if (chatroom == null) {
            return NotFound();
        }
        
        return Ok(chatroom.Users);
    }

    /// <summary>
    /// Adds a new user to the chatroom
    /// </summary>
    /// <response code="404">Chatroom not found</response>
    [HttpPost("{id}/user")]
    public async Task<ActionResult> PostUser(int id, int userId)
    {
		var chatroom = await this.context.Chatrooms.FindAsync(id);
        if (chatroom == null) {
            return NotFound();
        }

        var user = await this.context.Users.FindAsync(userId);
        if (user == null) {
            return NotFound();
        }

        chatroom.Users.Add(user);
        
        context.Chatrooms.Update(chatroom);
        await context.SaveChangesAsync();

        return Ok();
    }

	/// <summary>
    /// Gets all messages of the chatroom
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">Chatroom not found</response>
    [HttpGet("{id}/messages")]
    public async Task<IEnumerable<Message>> GetMessages(int id)
    {
		return this.context.Messages.Where(x => x.ChatroomId == id);
    }

    /// <summary>
    /// Adds a new message to the chatroom
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    [HttpPost("{id}/messages")]
    public async Task PostMessage(int id, Message message)
    {
		message.ChatroomId = id;
        message.SendAt = DateTime.Now;
        message.SeenAt = DateTime.MinValue;
		await this.context.Messages.AddAsync(message);

		await this.context.SaveChangesAsync();
    }
}
