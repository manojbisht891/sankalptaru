<?php
/**
 * @file
 * Shopping cart template.
 */
?>
<div class="wrapper">
  <div class="cart-icon"></div>
  <span class="cart_popup_count"><?php print $product_count; ?></span>
  <div id="cart-popup" style="display:none;">
    <?php print theme('commerce_cart_block', $variables['variables']); ?>
    <div class="popup-arrow"></div></div>
</div>
