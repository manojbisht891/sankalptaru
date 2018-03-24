/**
 * @file
 * Commerce Popup Cart javascript functions.
 */

(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.cartpopup_behavior = {
    attach: function(context, settings) {
      // Shopping cart block contents.
      if ($.isFunction($.fn.hoverIntent)) {
        $("#block-commerce-popup-cart-commerce-popup-cart").click(function(){
          var wrapper = $(this).find('#cart-popup');
          wrapper.toggle();
        });
        $("#block-commerce-popup-cart-commerce-popup-cart").hoverIntent({
          sensitivity: 7,
          interval: 50,
          over: function () {
            var wrapper = $(this).find('#cart-popup');
            wrapper.show();
          },
          timeout: 500,
          out: function () {
            $('#cart-popup').hide();
          }
        });
      }
    }
  }
})(jQuery, Drupal, this, this.document);
