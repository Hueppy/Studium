using System.Security.Claims;
using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Extensions;

public static class ControllerBaseExtension
{
    public static ActionResult<T> WithCurrentUser<T>(
        this ControllerBase controller,
        PfotenFreundeContext context,
        Func<User, ActionResult<T>> action)
    {
        var email = controller.HttpContext.User.FindFirst(ClaimTypes.Email);
        if (email == null)
        {
            return controller.Forbid();
        }
        var user = context.Users.FirstOrDefault(x => x.Email == email.Value);
        if (user == null)
        {
            return controller.Forbid();
        }

        return action(user);
    }

    public static ActionResult WithCurrentUser(
        this ControllerBase controller,
        PfotenFreundeContext context,
        Func<User, ActionResult> action)
    {
        var email = controller.HttpContext.User.FindFirst(ClaimTypes.Email);
        if (email == null)
        {
            return controller.Forbid();
        }
        var user = context.Users.FirstOrDefault(x => x.Email == email.Value);
        if (user == null)
        {
            return controller.Forbid();
        }

        return action(user);
    }

    public static bool IsAdministrator(this ControllerBase controller)
    {
        var roleClaim = controller.HttpContext.User.FindFirst(ClaimTypes.Role);
        return roleClaim != null
            && Role.TryParse<Role>(roleClaim.Value, out Role role)
            && role == Role.Administrator;
    }
}
