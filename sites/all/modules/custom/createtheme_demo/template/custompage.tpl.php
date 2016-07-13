<table border="1">
    <tr>
        <th colspan="3">Countries States Cities</th>
    </tr>
    <tr>
        <th>Country</th>
        <th>State</th>
        <th>City</th>
    </tr>
    <?php foreach ($result as $key => $value) { 
        ?><tr>
          <td><?php echo $value->country_name; ?></td>
          <td><?php echo $value->state_name; ?></td>
          <td><?php echo $value->city_name;?></td>
          </tr>
    <?php
    }?>
</table>