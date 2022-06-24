using System.Security.Claims;
using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class FriendController : ControllerBase
{
	private PfotenFreundeContext context;

	public FriendController(PfotenFreundeContext context)
	{
		this.context = context;
	}
	
    /// <summary>
    /// Retrieves friend list of user
    /// </summary>
    [HttpGet("{userId}")]
    public IEnumerable<User?> GetAll(int userId)
    {
        var friends = context.FriendRequests
            .Where(x => x.State == FriendRequestState.Accept && (x.ReceiverId == userId || x.SenderId == userId))
            .Select(x => x.ReceiverId == userId ? x.SenderId : x.ReceiverId);
        return context.Users.Where(x => friends.Contains(x.Id));
    }

    /// <summary>
    /// Sends a friend request to the specified user
    /// </summary>
    /// <response code="400">User is already befriended</response>
    [HttpPost("{userId}")]
    public ActionResult Create(int userId)
    {
        return this.WithCurrentUser(context, user =>
        {
            context.FriendRequests.Add(
                new FriendRequest
                {
                    Id = 0,
                    SendAt = DateTime.Now,
                    SeenAt = DateTime.MinValue,
                    State = FriendRequestState.Open,
                    ReceiverId = userId,
                    SenderId = user.Id
                });
            context.SaveChanges();
            return Ok();
        });
    }

    /// <summary>
    /// Removes a friendship
    /// </summary>
    /// <response code="404">User is not befriended</response>
    /// <response code="400">User is not befriended</response>
    [HttpDelete("{userId}")]
    public ActionResult Destroy(int userId)
    {
        return this.WithCurrentUser(context, user =>
        {
            var request = context.FriendRequests.FirstOrDefault(x => (x.SenderId == user.Id && x.ReceiverId == userId)
                                                                  || (x.SenderId == userId  && x.ReceiverId == user.Id));
            if (request == null)
            {
                return NotFound();
            }
            if (request.State != FriendRequestState.Accept)
            {
                return BadRequest();
            }
            request.State = FriendRequestState.Decline;
            context.FriendRequests.Update(request);
            context.SaveChanges();
            
            return Ok();
        }); 
    }

    /// <summary>
    /// Gets open friend requests of current user
    /// </summary>
    /// <response code="403">Current user is not avilable</response>
    [HttpGet("request")]
    public ActionResult<IEnumerable<FriendRequest>> GetOpenRequests()
    {
        return this.WithCurrentUser<IEnumerable<FriendRequest>>(context, 
            user => Ok(context.FriendRequests
                       .Where(x => x.State == FriendRequestState.Open && x.ReceiverId == user.Id))
        );
    }
    
    /// <summary>
    /// Changes the state of the open friend request
    /// </summary>
    /// <response code="403">Current user is not avilable</response>
    /// <response code="404">Request does not exist</response>
    [HttpPost("request/{id}")]
    public ActionResult PostRequestState(int id, FriendRequestState state)
    {
        return this.WithCurrentUser(context, user =>
        {
            var request = context.FriendRequests.Find(id);
            if (request == null)
            {
                return NotFound();
            }
            if (request.State != FriendRequestState.Open || request.ReceiverId != user.Id)
            {
                return Forbid();
            }
            request.State = state;
            context.FriendRequests.Update(request);
            context.SaveChanges();
            
            return Ok();
        });    
    }
}
