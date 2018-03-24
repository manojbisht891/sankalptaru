<?php

/**
 * @file
 * Commerce Popup Cart module admin functions.
 */

/**
 * Page callback for commerce popup cart configuration form.
 *
 * @return array
 *   Structure of the configuration form.
 */
function commerce_popup_cart_admin_form() {
  $form['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Commerce Popup Cart Configuration'),
  );
  $form['text']['commerce_popup_cart_empty_cart_msg'] = array(
    '#type'  => 'textarea',
    '#title' => t('Empty Cart Message'),
    '#default_value' => variable_get('commerce_popup_cart_empty_cart_msg', 'Your cart is empty.'),
    '#description' => 'Enter the text to be displayed in the popup when the cart is empty.',
  );
  $form['options']['commerce_popup_cart_show_empty_cart'] = array(
    '#type'  => 'checkbox',
    '#title' => t('Show the cart icon when empty?'),
    '#default_value' => variable_get('commerce_popup_cart_show_empty_cart', 0),
    '#description' => t('When this option is enabled the cart icon will be displayed even if their is nothing in the cart.'),
  );
  $form['options']['commerce_popup_cart_item_suffix'] = array(
    '#type'  => 'checkbox',
    '#title' => t('Show the suffix of the cart item.'),
    '#default_value' => variable_get('commerce_popup_cart_item_suffix', 0),
    '#description' => t("Examples: '2 items', '1 item'"),
  );
  $form['options']['commerce_popup_cart_line_items_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Line item types to be counted'),
    '#description' => t('Select the line item types that you want to be included in the counter.'),
    '#default_value' => variable_get('commerce_popup_cart_line_items_types', array('product' => 'product')),
    '#options' => commerce_popup_cart_line_items(),
    '#size' => 30,
  );
  return system_settings_form($form);
}
