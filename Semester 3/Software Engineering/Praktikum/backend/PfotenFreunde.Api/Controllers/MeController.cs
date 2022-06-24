using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class MeController : ControllerBase
{
	private PfotenFreundeContext context;

	public MeController(PfotenFreundeContext context)
	{
		this.context = context;
	}
	
    /// <summary>
    /// Gets the current user
    /// </summary>
    [HttpGet]
    public ActionResult<User> Get()
    {
		return this.WithCurrentUser<User>(context, user => user);
    }

    /// <summary>
    /// Gets matches of user
    /// </summary>
    [HttpGet("matches")]
    public ActionResult<IEnumerable<User>> GetMatches()
    {
        return this.WithCurrentUser(context, user =>
        {
            var selfIds = context.Ratings
                .Where(x => x.SenderId == user.Id && x.Type == RatingType.Attractive)
                .Select(x => x.UserId);
            var otherIds = context.Ratings
                .Where(x => x.UserId == user.Id && x.Type == RatingType.Attractive)
                .Select(x => x.SenderId);
            var ids = Enumerable.Intersect(selfIds, otherIds);
            
            return Ok(context.Users.Where(x => ids.Contains(x.Id)));
        });
    }

    /// <summary>
    /// Gets chatrooms of user
    /// </summary>
    [HttpGet("chatrooms")]
    public ActionResult<IEnumerable<Chatroom>> GetChatroom()
    {
        return this.WithCurrentUser<IEnumerable<Chatroom>>(context, user =>
        {
            var ids = context.Chatrooms
                .Where(x => x.Users.Any(y => y.Id == user.Id))
                .Select(x => x.Id);

            return Ok(context.Chatrooms.Where(x => ids.Contains(x.Id)));
        });
    }

    /// <summary>
    /// Set the current user status
    /// </summary>
    [HttpPost("status")]
    public ActionResult PostStatus(UserStatus status)
    {
        return this.WithCurrentUser(context, user =>
        {
            user.Status = status;
            context.Users.Update(user);
            context.SaveChanges();
            
            return Ok();
        });
    }

    
}
